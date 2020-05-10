#ifndef LEDWALLSTUDIO_HTTPCONNECTOR_H
#define LEDWALLSTUDIO_HTTPCONNECTOR_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QProgressDialog>
#include "Config.h"

class HttpConnector : public QObject
{
Q_OBJECT

public:
    // although this is only an object, a widget as parent is required to parent the progress-dialog
    explicit HttpConnector(QWidget *parent = nullptr);

    bool isConnected() const;

    LedWall::Config getConfig() const;

public slots:
    void connectToWall();

signals:
    void connected();
    void disconnected();
    void connectionStatusChanged(bool isConnected);

protected slots:
    void onHttpRequestFinished(QNetworkReply *reply);
    void onHttpRequestError(QNetworkReply::NetworkError replyError);
    void requestConfig();

protected:
    QNetworkAccessManager *m_networkAccessManager;
    quint16 m_pendingRequests = 0;
    QString getHost() const;

    LedWall::Config m_config;

    bool m_isConnected = false;
    void setIsConnected(bool isConnected);

    QProgressDialog *m_progressDialog;
    void initProgressDialog();
    // increases pending requests and shows the progress dialog
    void showProgressDialog();
    // decreases pending requests and hides the progress dialog if pending requests reached zero
    void hideProgressDialog();
};

#endif //LEDWALLSTUDIO_HTTPCONNECTOR_H
