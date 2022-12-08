#include "MainWindow.h"
#include "IOCContainer.h"
#include "ui_MainWindow.h"
#include "IChart.h"
#include "PieChart.h"
#include "BarChart.h"
#include "IDataReader.h"
#include "SqlDataReader.h"
#include "JsonDataReader.h"

#include <QDir>
#include <QFileDialog>

static const int DATA_SIZE = 10; //Статическая константа. Ограничение для считывания данных для коректного вывода

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_selectFolderButton_clicked() { //Выбор папки с файлами
    QString strs = QFileDialog::getExistingDirectory(this);
    QDir directory(strs); //QDir обеспечивает доступ к каталогов и их содержимому
    directory.setFilter(QDir::Files); //Устанавливаем фильтр
    QFileInfoList files = directory.entryInfoList(); //Получаем список файлов
    for (auto fileInfo : files) { //Проходимся по всем файлам
        ui->tableWidget->insertRow(ui->tableWidget->rowCount()); //Добавляем новую строчку в таблицу
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(fileInfo.fileName())); //Получаем имя файла и заполняем столбец Name
        QString sizeStr = QString::number(fileInfo.size()); //Получаем размер файла
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(sizeStr + "B")); //Заполняем столбец Size
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(fileInfo.suffix())); //Получаем тип файла и заполняем столбец Type
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(fileInfo.lastModified().toString())); //Получаем дату последнего изменения и заносим в столбец Date Modified
        filesPath.push_back(fileInfo.absoluteFilePath()); //Добавляем путь к файлу в общий список
    }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column) { //Выбор строчки в таблице
    currentFilePath = filesPath.at(row); //Получаем путь до файла из списка по номеру строчки и записываем его в переменную текущего файла
    int typeChart = ui->typeChartComboBox->currentIndex(); //Из combobox смотрим какой тип диаграммы выставлен для вывода
    if (typeChart == 0) { // 0 - Вертикальная диаграмма
        gContainer.RegisterInstance<IChart, BarChart>(); //Через IOC контейнер регистрируем диаграмму BarChart
    } else if (typeChart == 1) { // 1 - Круговая диаграмма
        gContainer.RegisterInstance<IChart, PieChart>(); //Через IOC контейнер регистрируем диаграмму PieChart
    }

    //Проверяем какой формат файла
    if (currentFilePath.endsWith(".sqlite")) { //Для файлов формата sqlite
        gContainer.RegisterInstance<IDataReader, SqlDataReader>(); //Через IOC контейнер регистрируем считыватель данных SqlDataReader
    } else if (currentFilePath.endsWith(".json")) { //Для файлов формата json
        gContainer.RegisterInstance<IDataReader, JsonDataReader>(); //Через IOC контейнер регистрируем считыватель данных JsonDataReader
    }
    on_Draw(); //Рисуем график
}

void MainWindow::on_typeChartComboBox_currentIndexChanged(int index) { //Выбор типа диаграммы в combobox
    if (index == 0) { // 0 - Вертикальная диаграмма
        gContainer.RegisterInstance<IChart, BarChart>(); //Через IOC контейнер регистрируем диаграмму BarChart
    } else if (index == 1) { // 1 - Круговая диаграмма
        gContainer.RegisterInstance<IChart, PieChart>(); //Через IOC контейнер регистрируем диаграмму PieChart
    }

    if (currentFilePath != nullptr) { //Если путь до текущего файла не нулевой
        on_Draw(); //Перерисовываем график
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1) { //Изменение чек бокса отображения цвета
    if (currentFilePath != nullptr) { //Если путь до текущего файла не нулевой
        on_Draw(); //Перерисовываем график
    }
}

void MainWindow::on_Draw() { //Рисуем график
    IChart *chart = gContainer.GetObject<IChart>().get(); //Получаем диаграмму из контейнера
    //Получаем считыватель данных из контейнера и считываем из текущего файла данные с ограничением по количеству DATA_SIZE
    QMap<QString, double> data = gContainer.GetObject<IDataReader>()->readData(currentFilePath, DATA_SIZE);
    bool isBlackWhiteColor = ui->checkBox->isChecked(); //Проверяем установлен ли цвет черно-белый
    QList <QColor> colors; //Инициализируем список цветов для графика
    for (int i = 0; i < data.size(); i++) { //Для всех данных создаем цвет
        if (isBlackWhiteColor) { //Если установлен цвет черно-белый
            int bwColor = i * 10;
            colors.push_back(QColor(bwColor, bwColor, bwColor)); //Создаем цвета черно-белых оттенков
        } else {
            int R = rand()%250;
            int G = rand()%250;
            int B = rand()%250;
            colors.push_back(QColor(R, G, B)); //Создаем цвета цветных оттенков
        }
    }

    chart->generate(data, colors); //Генерируем диаграмму
    chartView = new QChartView(chart->getChart(), ui->horizontalFrame); //Создаем отображение графика
    chartView->setMinimumSize(650, 550); //Устанавливаем размер
    chartView->show();
    ui->exportPdfButton->setEnabled(true); //Включаем кнопку Export PDF
}

void MainWindow::on_exportPdfButton_clicked() { //Сохранение диаграммы в pdf
    QFileDialog dialog(this); //Предоставляем диалоговое окно
    dialog.setFileMode(QFileDialog::Directory); //Устанавливаем для выбора дериктории
    QString pathSavePdf;
    if (dialog.exec()) {
        pathSavePdf = dialog.selectedFiles().first(); //Сохраняем в переменную путь до дериктории
    }

    QPdfWriter writer(pathSavePdf + "/" + "chart.pdf"); //Создаем объект для записи в pdf и указываем путь
    writer.setPageSize(QPageSize(QPageSize::A4)); //Устанавливаем размер страницы
    QPainter painter(&writer);
    chartView->render(&painter); //Создаем pdf файл
    painter.end();
}


