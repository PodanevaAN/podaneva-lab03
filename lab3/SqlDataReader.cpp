#include "SqlDataReader.h"

QMap<QString, double> SqlDataReader::readData(QString path, int count) { //Метод получения данных из sqlite
    QMap<QString, double> data; //Инициализируем переменную для хранения данных
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(path); //Подлючаем файл базыданных sqlite по пути path
    if (!sdb.open()) { //Проверем открыта ли база данных
        qDebug() << sdb.lastError().text(); //Если нет, то выводим сообщение об ошибке
    } else {
        QSqlQuery query("SELECT * FROM " + sdb.tables().takeFirst()); //Делаем запрос в базу для получения всех данных из таблицы
        while (query.next() && count != 0) { //Проходим по бд пока существует следующая запись и мы не считали необходимое количество (count != 0)
            data.insert(query.value(0).toString(), query.value(1).toDouble()); //Записываем значения из бд
            count--;
        }
    }
    return data; //Возвращаем данные
}
