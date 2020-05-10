#include "UdpConnector.h"
#include <QtCore/QDebug>

UdpConnector::UdpConnector(QObject *parent) : QObject(parent)
{
    m_socket = new QUdpSocket(this);

    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(m_socket, &QUdpSocket::connected, this, &UdpConnector::onSocketConnected);

    m_socket->connectToHost("10.13.37.222", 47011);
}

void UdpConnector::sendBitmap(const Bitmap &bitmap)
{
//    qDebug() << "sendBitmap";
//    qDebug() << "socket state" << m_socket->state();

    QColor aPixelsColor = bitmap[QPoint(0, 0)];

    QByteArray pkt;
    pkt.resize(7);
    pkt[0] = 0x10; // protocol
    pkt[1] = 0x00; // settings

    pkt[2] = 0x00; // x
    pkt[3] = 0x00; // y

//    pkt[4] = 0xff; // r
//    pkt[5] = 0x00; // g
//    pkt[6] = 0xff; // b

    pkt[4] = aPixelsColor.red();
    pkt[5] = aPixelsColor.green();
    pkt[6] = aPixelsColor.blue();

    m_socket->write(pkt);
}

void UdpConnector::onSocketConnected()
{
    qDebug() << "CONNECTED! :)";
}

void UdpConnector::onSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "onSocketError" << socketError;
}
