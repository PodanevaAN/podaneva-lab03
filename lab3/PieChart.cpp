#include "PieChart.h"

void PieChart::generate(QMap<QString, double> data, QList<QColor> colors) { //Метод генерации круговой диаграммы
    chart = new QChart(); //Инициализируем диаграмму
    QPieSeries *pieSeries = new QPieSeries(); //Создаем фрагменты диаграммы
    int i = 0; //Итератор для списка цветов
    for (auto entry = data.begin(); entry != data.end(); entry++) { //Проходимся по всем данным
        QPieSlice *pieSlice = pieSeries->append(entry.key(), entry.value()); //Создаем фрагмент диаграммы и задаем значения
        pieSlice->setColor(colors.at(i)); //Устанавливаем цвет
        i++;
    }
    chart->addSeries(pieSeries); //Добавляем фрагменты в диаграмму
    chart->setTitle("Pie chart"); //Задаем заголовок
    chart->setAnimationOptions(QChart::SeriesAnimations); //Устанавливаем параметры анимации для диаграммы
}

QChart *PieChart::getChart() {
    return chart; //Возвращаем диаграмму
}
