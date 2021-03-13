#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include "qcustomplot.h"

class Plotter : public QObject
{
    Q_OBJECT
public:
    explicit Plotter(QObject *parent = nullptr, QCustomPlot* qCustPlot = nullptr);
    void testBasicSetup();

    void setupRealTimeGraph();

private:
    QCustomPlot* m_plot;

public slots:
    void updateGraph(const double key, const double temp);
signals:

};

#endif // PLOTTER_H
