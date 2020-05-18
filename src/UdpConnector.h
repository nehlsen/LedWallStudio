#ifndef LEDWALLSTUDIO_UDPCONNECTOR_H
#define LEDWALLSTUDIO_UDPCONNECTOR_H

#include <QtNetwork/QUdpSocket>
#include "Bitmap.h"

class UdpConnector : public QObject
{
Q_OBJECT

public:
    explicit UdpConnector(QObject *parent = nullptr);

    void sendBitmap(const Bitmap &bitmap);

protected slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onSocketConnected();

    void continueSend();

protected:
    QUdpSocket *m_socket;
    QByteArrayList m_sendQueue;
};

#endif //LEDWALLSTUDIO_UDPCONNECTOR_H
