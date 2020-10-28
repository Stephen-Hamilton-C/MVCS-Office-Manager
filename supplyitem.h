#ifndef SUPPLYITEM_H
#define SUPPLYITEM_H

#include <QJsonObject>
#include <QString>

class SupplyItem {
public:

    SupplyItem(QString name, int count, int lowCountThreshold = 0, std::map<QString, QString> properties = NULL);

    QString name;
    int count;
    int lowCountThreshold;
    std::map<QString, QString> properties;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

};

#endif // SUPPLYITEM_H
