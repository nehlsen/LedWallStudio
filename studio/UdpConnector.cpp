#include "UdpConnector.h"
#include <QtCore/QSettings>
#include <QtCore/QTimer>

#define UDP_CHUNK_SIZE 128
#define SEND_DELAY 30

namespace LedWall::Studio {

UdpConnector::UdpConnector(QObject *parent) : QObject(parent)
{
    m_socket = new QUdpSocket(this);

    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(m_socket, &QUdpSocket::connected, this, &UdpConnector::onSocketConnected);

    auto host = QSettings().value("Settings/host", "ledwall.local").toString();
    auto port = QSettings().value("Settings/udp_port", 47011).toInt();
    m_socket->connectToHost(host, port);
}

void UdpConnector::sendBitmap(const Bitmap &bitmap)
{
    m_sendQueue.append(bitmap.toPixelStreamChunked(UDP_CHUNK_SIZE));
    QTimer::singleShot(SEND_DELAY, this, &UdpConnector::continueSend);
}

void UdpConnector::onSocketConnected()
{
//    qDebug() << "CONNECTED! :)";
}

void UdpConnector::onSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "onSocketError" << socketError;
}

void UdpConnector::continueSend()
{
    if (m_sendQueue.isEmpty()) {
        return;
    }

    QByteArray chunk = m_sendQueue.takeFirst();
    m_socket->write(chunk);

    QTimer::singleShot(SEND_DELAY, this, &UdpConnector::continueSend);
}

}
