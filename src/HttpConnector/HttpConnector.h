#ifndef LEDWALLSTUDIO_HTTPCONNECTOR_H
#define LEDWALLSTUDIO_HTTPCONNECTOR_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QProgressDialog>
#include "Config.h"
#include "Mode.h"

class HttpConnector : public QObject
{
Q_OBJECT

public:
    // although this is only an object, a widget as parent is required to parent the progress-dialog
    explicit HttpConnector(QWidget *parent = nullptr);

    bool isConnected() const;

    LedWall::Config getConfig() const;
    void setConfig(const LedWall::Config& config);

    LedWall::ModeList getModes() const;
    LedWall::Mode getMode() const;
    void setMode(int modeIndex);

public slots:
    void connectToWall();

signals:
    void connected();
    void disconnected();
    void connectionStatusChanged(bool isConnected);

    void configChanged();
    void modesChanged();
    void modeChanged();

protected slots:
    void onHttpRequestFinished(QNetworkReply *reply);
    void onHttpRequestError(QNetworkReply::NetworkError replyError);
    void requestConfig();
    void requestModes();
    void requestMode();

    void onConnectCanceled();

protected:
    QNetworkAccessManager *m_networkAccessManager;
    QList<QNetworkReply*> m_pendingRequests;
    void addPendingRequest(QNetworkReply *reply);
    void removePendingRequest(QNetworkReply *reply);

    QString getHost() const;

    LedWall::Config m_config;
    LedWall::ModeList m_modes;
    LedWall::Mode m_mode;

    bool m_isConnected = false;
    void setIsConnected(bool isConnected);

    QProgressDialog *m_progressDialog;
    void initProgressDialog();

    void apiGet(const QString &apiEndpoint);
    void apiPost(const QString &apiEndpoint, const QByteArray &data);
};

#endif //LEDWALLSTUDIO_HTTPCONNECTOR_H
