#include "BarChart.h"

void BarChart::generate(QMap<QString, double> data, QList<QColor> colors) { //Метод генерации вертикальной диаграммы
    chart = new QChart(); //Инициализируем диаграмму
    QBarSeries *barSeries = new QBarSeries(); //Создаем вертикальные столбцы
    int i = 0; //Итератор для списка цветов
    for (auto entry = data.begin(); entry != data.end(); entry++) { //Проходимся по всем данным
        QBarSet *barSet = new QBarSet(entry.key()); //Создаем новый вертикальный столбец и задаем значения label
        *barSet << entry.value(); //Задаем значение в столбец
        barSet->setColor(colors.at(i)); //Устанавливаем цвет
        barSeries->append(barSet); //Добавляем вертикальный столбец
        i++;
    }
    chart->addSeries(barSeries); //Добавляем столбцы в диаграмму
    chart->createDefaultAxes(); //Создаем оси для диаграммы
    chart->setTitle("Bar chart"); //Задаем заголовок
    chart->setAnimationOptions(QChart::SeriesAnimations); //Устанавливаем параметры анимации для диаграммы
}

QChart *BarChart::getChart() {
    return chart; //Возвращаем диаграмму
}
