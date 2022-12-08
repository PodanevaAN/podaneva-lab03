#ifndef ICHART_H
#define ICHART_H

#include <QtCharts>


class IChart {
public:
    //Класс QMap - это шаблонный класс, который предоставляет ассоциативный массив позволяющий хранить пары вида (ключ, значение)
    virtual void generate(QMap<QString, double> data, QList <QColor> colors) = 0; //Функция для генерации диаграммы
    virtual QChart *getChart() = 0; //Функция для получения диаграммы
};

#endif // ICHART_H
