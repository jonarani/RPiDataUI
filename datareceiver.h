#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QThread>

class DataReceiver : public QThread
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);

protected:
    void run() override;

private:
    bool flag = 0;

signals:
    void dataReady(const double key, const double temp);

public slots:
    void produceData();
};

#endif // DATARECEIVER_H
