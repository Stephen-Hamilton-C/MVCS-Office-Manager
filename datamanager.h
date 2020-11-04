#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "cadet.h"
#include "inspectioncard.h"
#include "supplyitem.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class DataManager {
public:

    DataManager();

    static QMap<int, Cadet*> cadets;
    static QMap<QString, SupplyItem*> items;
    static QMap<int, InspectionCard*> insCards;

    static void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    static void readFromFile();
    void writeToFile() const;

};

#endif // DATAMANAGER_H
