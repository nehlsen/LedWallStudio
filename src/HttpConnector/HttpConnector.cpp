#include "HttpConnector.h"
#include <QtNetwork/QNetworkReply>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtCore/QSettings>

#define LEDWALL_API_BASE "/api/v1"
#define LEDWALL_API_GET_CONFIG LEDWALL_API_BASE + "/config"

HttpConnector::HttpConnector(QWidget *parent): QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager;
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &HttpConnector::onHttpRequestFinished);

    initProgressDialog();

    // TODO if auto-connect = true
    QTimer::singleShot(0, this, &HttpConnector::connectToWall);
}

LedWall::Config HttpConnector::getConfig() const
{
    return m_config;
}

void HttpConnector::setConfig(const LedWall::Config& config)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://" + getHost() + LEDWALL_API_GET_CONFIG));
    request.setRawHeader("User-Agent", "LedWallStudio 1.0");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    showProgressDialog();
    QNetworkReply *reply = m_networkAccessManager->post(request, config.toJson().toJson());
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &HttpConnector::onHttpRequestError);
}

void HttpConnector::connectToWall()
{
    requestConfig();
}

bool HttpConnector::isConnected() const
{
    return m_isConnected;
}

void HttpConnector::onHttpRequestFinished(QNetworkReply *reply)
{
    qDebug() << "onHttpRequestFinished" << reply->request().url();

    if (reply->request().url().toString().endsWith(QString() + LEDWALL_API_GET_CONFIG)) {
        m_config = LedWall::Config::fromJson(QJsonDocument::fromJson(reply->readAll()));
    }

    hideProgressDialog();
    setIsConnected(reply->error() == QNetworkReply::NoError);
}

void HttpConnector::onHttpRequestError(QNetworkReply::NetworkError replyError)
{
//    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "onHttpRequestError" << replyError;
}

void HttpConnector::requestConfig()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://" + getHost() + LEDWALL_API_GET_CONFIG));
    request.setRawHeader("User-Agent", "LedWallStudio 1.0");

    showProgressDialog();
    QNetworkReply *reply = m_networkAccessManager->get(request);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &HttpConnector::onHttpRequestError);
}

void HttpConnector::setIsConnected(bool isConnected)
{
    m_isConnected = isConnected;

    if (isConnected) emit connected();
    else emit disconnected();
    emit connectionStatusChanged(isConnected);
}

void HttpConnector::initProgressDialog()
{
    m_progressDialog = new QProgressDialog(qobject_cast<QWidget*>(parent()));
    m_progressDialog->setMinimum(0);
    m_progressDialog->setMaximum(0);
    m_progressDialog->setLabelText(tr("Connecting LedWall..."));
}

void HttpConnector::showProgressDialog()
{
    m_pendingRequests++;

    m_progressDialog->show();
}

void HttpConnector::hideProgressDialog()
{
    m_pendingRequests--;

    if (m_pendingRequests == 0) {
        m_progressDialog->hide();
    }
}

QString HttpConnector::getHost() const
{
    return QSettings().value("Settings/host", "ledwall.local").toString();
}

