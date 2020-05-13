#include "HttpConnector.h"
#include <QtNetwork/QNetworkReply>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QSettings>
#include <QtCore/QJsonObject>

#define LEDWALL_API_BASE QString("/api/v1")
#define LEDWALL_API_GET_CONFIG LEDWALL_API_BASE + "/config"
#define LEDWALL_API_POST_CONFIG LEDWALL_API_GET_CONFIG
#define LEDWALL_API_GET_MODES LEDWALL_API_BASE + "/led/modes"
#define LEDWALL_API_GET_MODE LEDWALL_API_BASE + "/led/mode"
#define LEDWALL_API_POST_MODE LEDWALL_API_GET_MODE

HttpConnector::HttpConnector(QWidget *parent): QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager;
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &HttpConnector::onHttpRequestFinished);

    initProgressDialog();

    if (QSettings().value("Settings/auto_connect", true).toBool()) {
        m_isConnected = !m_isConnected; // to force the connected signal to be emitted
        QTimer::singleShot(0, this, &HttpConnector::connectToWall);
    }
}

LedWall::Config HttpConnector::getConfig() const
{
    return m_config;
}

void HttpConnector::setConfig(const LedWall::Config& config)
{
    if (m_config == config) {
        return;
    }

    apiPost(LEDWALL_API_POST_CONFIG, m_config.deltaAsJson(config).toJson());
}

LedWall::ModeList HttpConnector::getModes() const
{
    return m_modes;
}

LedWall::Mode HttpConnector::getMode() const
{
    return m_mode;
}

void HttpConnector::setMode(int modeIndex)
{
    QJsonObject req;
    req.insert("index", modeIndex);

    apiPost(LEDWALL_API_POST_MODE, QJsonDocument(req).toJson());
}

void HttpConnector::connectToWall()
{
    QTimer::singleShot(0, this, &HttpConnector::requestConfig);
    QTimer::singleShot(0, this, &HttpConnector::requestModes);
    QTimer::singleShot(0, this, &HttpConnector::requestMode);
}

bool HttpConnector::isConnected() const
{
    return m_isConnected;
}

void HttpConnector::onHttpRequestFinished(QNetworkReply *reply)
{
    const QString &requestUrl = reply->request().url().toString();
    const bool replySuccessful = reply->error() == QNetworkReply::NoError;

    qDebug() << "onHttpRequestFinished" << reply->error() << requestUrl;

    if (replySuccessful && requestUrl.endsWith(LEDWALL_API_GET_CONFIG)) {
        m_config = LedWall::Config::fromJson(QJsonDocument::fromJson(reply->readAll()));
        emit configChanged();
    }
    if (replySuccessful && requestUrl.endsWith(LEDWALL_API_GET_MODES)) {
        m_modes = LedWall::ModeList::fromJson(QJsonDocument::fromJson(reply->readAll()));
        emit modesChanged();
    }
    if (replySuccessful && requestUrl.endsWith(LEDWALL_API_GET_MODE)) {
        m_mode = LedWall::Mode::fromJson(QJsonDocument::fromJson(reply->readAll()).object());
        emit modeChanged();
    }

    hideProgressDialog();
    setIsConnected(replySuccessful);
}

void HttpConnector::onHttpRequestError(QNetworkReply::NetworkError replyError)
{
//    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "onHttpRequestError" << replyError;
}

void HttpConnector::requestConfig()
{
    apiGet(LEDWALL_API_GET_CONFIG);
}

void HttpConnector::requestModes()
{
    apiGet(LEDWALL_API_GET_MODES);
}

void HttpConnector::requestMode()
{
    apiGet(LEDWALL_API_GET_MODE);
}

QString HttpConnector::getHost() const
{
    return QSettings().value("Settings/host", "ledwall.local").toString();
}

void HttpConnector::setIsConnected(bool isConnected)
{
    if (m_isConnected == isConnected) {
        return;
    }

    m_isConnected = isConnected;

    if (isConnected) emit connected();
    else emit disconnected();
    emit connectionStatusChanged(isConnected);
}

void HttpConnector::initProgressDialog()
{
    m_progressDialog = new QProgressDialog(qobject_cast<QWidget*>(parent()));
    m_progressDialog->setWindowModality(Qt::WindowModal);
    m_progressDialog->setMinimum(0);
    m_progressDialog->setMaximum(0);
    m_progressDialog->setWindowTitle(tr("Connecting..."));
    m_progressDialog->setLabelText(tr("Connecting LedWall..."));
    m_progressDialog->setVisible(false);

    // FIXME cancel button is displayed and closes the dialog but has no meaningful function
}

void HttpConnector::showProgressDialog()
{
    m_pendingRequests++;

    m_progressDialog->show();
}

void HttpConnector::hideProgressDialog()
{
    if (m_pendingRequests > 0) {
        m_pendingRequests--;
    }

    if (m_pendingRequests == 0) {
        m_progressDialog->hide();
    }
}

void HttpConnector::apiGet(const QString &apiEndpoint)
{
    qDebug() << __func__  << apiEndpoint;

    QNetworkRequest request;
    request.setUrl(QUrl("http://" + getHost() + apiEndpoint));
    request.setRawHeader("User-Agent", "LedWallStudio 1.0");

    showProgressDialog();
    QNetworkReply *reply = m_networkAccessManager->get(request);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &HttpConnector::onHttpRequestError);
}

void HttpConnector::apiPost(const QString &apiEndpoint, const QByteArray &data)
{
    qDebug() << __func__  << apiEndpoint;

    QNetworkRequest request;
    request.setUrl(QUrl("http://" + getHost() + apiEndpoint));
    request.setRawHeader("User-Agent", "LedWallStudio 1.0");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    showProgressDialog();
    qDebug() << "POST" << data;
    QNetworkReply *reply = m_networkAccessManager->post(request, data);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &HttpConnector::onHttpRequestError);
}

