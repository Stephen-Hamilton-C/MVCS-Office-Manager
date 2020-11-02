#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "cadet.h"
#include "inspectioncard.h"
#include "supplyitem.h"

#include <QJsonObject>

class DataManager {
public:

    DataManager();

    static QMap<int, Cadet*> cadets;
    static QMap<QString, SupplyItem*> items;
    static QMap<int, InspectionCard*> insCards;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

};

#endif // DATAMANAGER_H
