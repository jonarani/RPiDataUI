#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotter.h"
#include "datareceiver.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DataReceiver *m_pReceiverThread = nullptr;

private slots:


private:
    Ui::MainWindow *ui;
    Plotter *plotter;
};
#endif // MAINWINDOW_H
