#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class DataReceiver : public QThread
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);

protected:
    void run() override;

private:
    bool flag = 0;

    QTcpSocket *m_socket;
    void doConnect();

signals:
    void dataReady(const double key, const double temp, const double hum);

public slots:
    void produceData();

    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
};

#endif // DATARECEIVER_H
