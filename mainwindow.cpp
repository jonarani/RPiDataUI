#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plotter = new Plotter(this, ui->plotWidget);
    plotter->setupRealTimeGraph();

    m_pReceiverThread = new DataReceiver;
    connect(m_pReceiverThread, &DataReceiver::finished, m_pReceiverThread, &QObject::deleteLater);
    connect(m_pReceiverThread, &DataReceiver::dataReady, this->plotter, &Plotter::updateGraph);
    // TODO: stop slot for thread and quit button for application

    m_pReceiverThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
