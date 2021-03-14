#include "plotter.h"

#define START_TIME 0
#define TIME_RANGE 7

Plotter::Plotter(QObject *parent, QCustomPlot* qCustPlot) : QObject(parent)
{
    m_plot = qCustPlot;
}

void Plotter::setupRealTimeGraph()
{
    m_plot->addGraph();
    m_plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);   // Circles on data points

    m_plot->xAxis->setLabel("Time (s)");
    m_plot->yAxis->setLabel("Temperature");

    m_plot->xAxis->setRange(START_TIME, TIME_RANGE);
    m_plot->yAxis->setRange(0, 1);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_plot->xAxis->setTicker(timeTicker);

    m_plot->replot();
}

// SLOT
void Plotter::updateGraph(const double key, const double y)
{
    static double lastPointKey = 0;

    if(key - lastPointKey > 0.002) // Is this check necessary
    {
        m_plot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
        lastPointKey = key;
    }

    m_plot->graph(0)->rescaleValueAxis();
    if(key >= TIME_RANGE)
        m_plot->xAxis->setRange(key, TIME_RANGE, Qt::AlignRight);
    else
        m_plot->xAxis->setRange(START_TIME, TIME_RANGE);

    m_plot->replot();
}

void Plotter::testBasicSetup()
{
    QVector<double> x(30), y(30);
    for(int i = 0; i < 30; ++i)
    {
        x[i] = i;
        y[i] = i-7;
    }

    m_plot->addGraph();
    m_plot->graph(0)->setData(x, y);

    m_plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    m_plot->graph(0)->setLineStyle(QCPGraph::lsNone);   // No lines connecting points
    m_plot->xAxis->setRange(0, 30);
    m_plot->yAxis->setRange(-10, 30);

    m_plot->xAxis->setLabel("Time (s)");
    m_plot->yAxis->setLabel("Temperature");

    m_plot->replot();
}
