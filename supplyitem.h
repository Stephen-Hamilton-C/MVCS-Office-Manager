#ifndef SUPPLYITEM_H
#define SUPPLYITEM_H

#include <QJsonObject>

class SupplyItem {
public:

    SupplyItem(QString name, int count, int lowCountThreshold = 0, QVariantMap properties = QVariantMap());

    QString name;
    int count;
    int lowCountThreshold;
    QVariantMap properties;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

};

#endif // SUPPLYITEM_H
