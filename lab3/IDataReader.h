#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QString>


class IDataReader {
public:
    //Метод получения данных из файла
    virtual QMap<QString, double> readData(QString path, int count) = 0;
};

#endif //IDATAREADER_H
