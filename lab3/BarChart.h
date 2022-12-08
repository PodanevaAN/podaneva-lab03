#ifndef BARCHART_H
#define BARCHART_H

#include "IChart.h"


class BarChart : public IChart {
private:
    QChart *chart;

public:
    void generate(QMap<QString, double> data, QList<QColor> colors);
    QChart *getChart();
};

#endif // BARCHART_H
