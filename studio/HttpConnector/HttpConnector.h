#ifndef LEDWALLSTUDIO_HTTPCONNECTOR_H
#define LEDWALLSTUDIO_HTTPCONNECTOR_H

#include <QtWidgets/QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QProgressDialog>
#include "Config.h"
#include <WallController/WallController.h>

class HttpConnector : public WallController
{
Q_OBJECT

public:
    // although this is only an object, a widget as parent is required to parent the progress-dialog
    explicit HttpConnector(QWidget *parent = nullptr);

    LedWall::Config getConfig() const;
    void setConfig(const LedWall::Config& config);

    void setModeByIndex(int modeIndex) override;
    void setModeByName(const QString &name) override;

    void setModeOptions(const LedWallStudio::ModeOptions &options) override;

public slots:
    void connectToWall();

signals:
    void configChanged();

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

    QProgressDialog *m_progressDialog;
    void initProgressDialog();

    void apiGet(const QString &apiEndpoint);
    void apiPost(const QString &apiEndpoint, const QByteArray &data);
};

#endif //LEDWALLSTUDIO_HTTPCONNECTOR_H
