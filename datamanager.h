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

	static QMap<QString, Cadet> cadets;
	static QMap<QString, SupplyItem> items;
	static QMap<QString, InspectionCard> insCards;

    static void read(const QJsonObject& json);
    static void write(QJsonObject& json);

    static void readFromFile();
    static void writeToFile();

};

#endif // DATAMANAGER_H
