#ifndef SQLDATAREADER_H
#define SQLDATAREADER_H

#include <QtSql>
#include "IDataReader.h"


class SqlDataReader : public IDataReader {
public:
    QMap<QString, double> readData(QString path, int count);
};

#endif // SQLDATAREADER_H
