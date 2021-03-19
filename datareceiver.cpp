#include "datareceiver.h"
#include <QTime>
#include <QAbstractSocket>

QString RPI_IP_ADDR = "192.168.1.157";
quint16 PORT_NUM = 47777;

static bool isConnected;

DataReceiver::DataReceiver(QObject *parent) : QThread(parent)
{
}

void DataReceiver::run()
{
    double temp = 20;
    double hum = 40;
    QByteArray receivedData;

    doConnect();
    sleep(1);
    qDebug() << isConnected;

    while(isConnected)
    {
        if(m_socket->waitForReadyRead())
        {
            receivedData = m_socket->readAll();
            qDebug() << receivedData;
            auto dataList = receivedData.split('|');
            temp = dataList.first().toDouble();
            hum = dataList.back().toDouble();

            static QTime time(QTime::currentTime());
            double key = time.elapsed() / 1000.0;

            emit dataReady(key, temp, hum);
        }
    }
}

void DataReceiver::doConnect()
{
    m_socket = new QTcpSocket();

    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, &QTcpSocket::disconnected, this, &DataReceiver::disconnected);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &DataReceiver::bytesWritten);
    connect(m_socket, &QIODevice::readyRead, this, &DataReceiver::readyRead);

    qDebug() << "connecting...";

    m_socket->connectToHost(RPI_IP_ADDR, PORT_NUM, QIODevice::ReadWrite, QAbstractSocket::IPv4Protocol);

    if(!m_socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << m_socket->errorString();
    }
}

void DataReceiver::connected()
{
    isConnected = true;
    qDebug() << "connected...";
}

void DataReceiver::disconnected()
{
    isConnected = false;
    qDebug() << "disconnected...";
}

void DataReceiver::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void DataReceiver::readyRead()
{
    // qDebug() << "ready...";
    // qDebug() << m_socket->readAll();
}
