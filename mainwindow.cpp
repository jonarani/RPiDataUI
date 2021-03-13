#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);

    plotter = new Plotter(this, ui->plotWidget);
    plotter->setupRealTimeGraph();

    m_pReceiverThread = new DataReceiver;
    connect(m_pReceiverThread, &DataReceiver::finished, m_pReceiverThread, &QObject::deleteLater);
    connect(m_pReceiverThread, &DataReceiver::dataReady, this->plotter, &Plotter::updateGraph);
    // TODO: stop slot for thread and quit button for application

    connect(timer, &QTimer::timeout, m_pReceiverThread, &DataReceiver::produceData);

    m_pReceiverThread->start();
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}
