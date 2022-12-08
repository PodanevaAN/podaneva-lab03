#include "JsonDataReader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QMap<QString, double> JsonDataReader::readData(QString path, int count) { //Метод получения данных из json
    QMap<QString, double> data; //Инициализируем переменную для хранения данных
    QFile file(path); //Файл по пути path
    file.open(QIODevice::ReadOnly | QIODevice::Text); //Открываем файл на чтение
    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array(); //Читаем данные с файла и преобразуем в массив json значений
    for (const QJsonValue &v : jsonArray) { //Проходимся по массиву
        if (v.isObject()) { //Проверяем содержит ли объект
            QJsonObject obj = v.toObject(); //Получаем объект
            data.insert(obj["Time"].toString(), obj["Value"].toDouble()); //Достаем по ключам Time и Value данные из объекта json и сохраняем
            count--;
        }
        if (count == 0) { //Если мы считали необходимое количество данных выходим из цикла
            break;
        }
    }
    return data; //Возвращаем данные
}
