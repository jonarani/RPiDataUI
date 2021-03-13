#include "datareceiver.h"
#include <QTime>
DataReceiver::DataReceiver(QObject *parent) : QThread(parent)
{

}

void DataReceiver::run()
{
    double y = 15;
    while(true)
    {
        // TODO: Conditional variable or mutex so that thread could go to sleep and not waste any CPU time
        //       TCPSocket for incoming data
        if(flag)
        {
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
