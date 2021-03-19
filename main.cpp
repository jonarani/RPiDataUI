#include "mainwindow.h"
#include <QApplication>

// TODO list
/*
 *  1. Can enter IP and port, and try to connect
 *  2. Can choose what kind of data is received (temp and hum, or accelerometer) and start receiing
 *  3. Can pause the receiveing, then continue
 *  4. Can stop the receiving and then choose the other kind of data
 *  5. Saves graph data to DB and/or to files
 *  6. Can open files to plot the data
 *  7. Quit button
 *  8. Replace QTime(deprecated) with QElapsedTimer
 *  9. When server disconnects then can reconnect and continue
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
