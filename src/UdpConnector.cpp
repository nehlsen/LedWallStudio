#include "UdpConnector.h"
#include <QtCore/QSettings>
//#include <QtCore/QDebug>

#define UDP_CHUNK_SIZE 128

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
    QByteArrayList chunks = bitmap.toPixelStreamChunked(UDP_CHUNK_SIZE);
//    qDebug() << "sendBitmap," << chunks.size() << "chunks";
    for (QByteArray chunk : chunks) {
//        qDebug() << "CHUNK" << chunk;
        m_socket->write(chunk); // TODO error handling ?!
    }
}

void UdpConnector::onSocketConnected()
{
//    qDebug() << "CONNECTED! :)";
}

void UdpConnector::onSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "onSocketError" << socketError;
}
