#ifndef SUPPLYITEM_H
#define SUPPLYITEM_H

#include <QJsonObject>
#include <QString>

class SupplyItem {
public:

    SupplyItem(QString name, int count, int lowCountThreshold = 0, QMap<QVariant, QVariant> properties = QMap<QVariant, QVariant>());

    QString name;
    int count;
    int lowCountThreshold;
    QMap<QVariant, QVariant> properties;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

};

#endif // SUPPLYITEM_H
