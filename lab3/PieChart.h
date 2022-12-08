#ifndef PIECHART_H
#define PIECHART_H

#include "IChart.h"


class PieChart : public IChart {
private:
    QChart *chart;

public:
    void generate(QMap<QString, double> data, QList<QColor> colors);
    QChart *getChart();
};

#endif // PIECHART_H
