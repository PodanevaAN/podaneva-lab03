#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCharts>
#include <QChartView>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFolderButton_clicked(); //Фнкция вызывается при нажатии на кнопку Select folder

    void on_tableWidget_cellClicked(int row, int column); //Функция вызывается при нажатии на ячейку в таблице файлов

    void on_typeChartComboBox_currentIndexChanged(int index); //Функция вызывается при изменении типа диаграммы в ComboBox (Bar Chart, Pie Chart)

    void on_Draw(); //Функция отрисовки диаграммы

    void on_exportPdfButton_clicked(); //Фнкция вызывается при нажатии на кнопку Export PDF

    void on_checkBox_stateChanged(int arg1); //Функция вызывается при изменении чек бокса черно-белых цветов

private:
    Ui::MainWindow *ui;
    QStringList filesPath; //Список путей до файлов в папке
    QString currentFilePath; //Путь до выбранного файла в папке
    QChartView *chartView; //Отображение диаграммы
};
#endif // MAINWINDOW_H
