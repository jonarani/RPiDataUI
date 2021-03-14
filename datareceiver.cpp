#include "datareceiver.h"
#include <QTime>
#include <QAbstractSocket>

#define RPI_IP_ADDR "192.168.1.157"
#define PORT_NUM 50000

static bool isConnected;

DataReceiver::DataReceiver(QObject *parent) : QThread(parent)
{

}

void DataReceiver::run()
{
    double y = 15;

    doConnect();
    qDebug() << isConnected;

    while(isConnected)
    {
        // TODO: Conditional variable or mutex so that thread could go to sleep and not waste any CPU time
        //       TCPSocket for incoming data
        if(flag)
        {
            // qint64 ret = m_socket->write("Data", qstrlen("Data"));
            // qDebug() << ret;

            static QTime time(QTime::currentTime());
            double key = time.elapsed() / 1000.0;
            flag = 0;

            if(y >= 50)
                y = -20;
            else
                y++;

            emit dataReady(key, y);
        }
    }
}

void DataReceiver::produceData()
{
    flag = 1;
}

void DataReceiver::doConnect()
{
    m_socket = new QTcpSocket();

    connect(m_socket, &QTcpSocket::connected, this, &DataReceiver::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &DataReceiver::disconnected);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &DataReceiver::bytesWritten);
    connect(m_socket, &QTcpSocket::readyRead, this, &DataReceiver::readyRead);

    qDebug() << "connecting...";

    m_socket->connectToHost(RPI_IP_ADDR, PORT_NUM, QIODevice::ReadWrite, QAbstractSocket::IPv4Protocol);

    if(!m_socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << m_socket->errorString();
    }
    else
    {
        isConnected = true;
    }
}

void DataReceiver::connected()
{
    qDebug() << "connected...";
}

void DataReceiver::disconnected()
{
    qDebug() << "disconnected...";
}

void DataReceiver::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void DataReceiver::readyRead()
{
    qDebug() << "reading...";

    qDebug() << m_socket->readAll();
}
