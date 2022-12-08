#ifndef JSONDATAREADER_H
#define JSONDATAREADER_H

#include <QMap>
#include "IDataReader.h"


class JsonDataReader : public IDataReader {
public:
    QMap<QString, double> readData(QString path, int count);
};

#endif // JSONDATAREADER_H
