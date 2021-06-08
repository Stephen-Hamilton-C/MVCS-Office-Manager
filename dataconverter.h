#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QJsonObject>

class DataConverter
{
public:
    DataConverter();

    static void convert(QJsonObject &json);
};

#endif // DATACONVERTER_H
