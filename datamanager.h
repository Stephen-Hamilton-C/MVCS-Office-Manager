/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "cadet.h"
#include "inspectioncard.h"
#include "supplyitem.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

/**
 * @brief An interface between the program and the files that store the data for this application.
 */
class DataManager {
public:

    DataManager();

	/**
	 * @brief All the cadets that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, Cadet> cadets;
	/**
	 * @brief All the supply items that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, SupplyItem> items;
	/**
	 * @brief All the inspection logs that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, InspectionCard> insCards;

    static QStringList itemCategories;

	/**
	 * @brief Reads all data from a QJsonObject and loads it into memory.
	 * @param The JSON file, converted into a QJsonObject.
	 */
    static void read(const QJsonObject& json);
	/**
	 * @brief Converts data from memory to a QJsonObject to be written to a file.
	 * @param The QJsonObject, to be converted into a file later.
	 */
    static void write(QJsonObject& json);

	/**
	 * @brief Converts a JSON file to a QJsonObject and then stores it.
	 */
    static void readFromFile();
	/**
	 * @brief Writes stored data out to a JSON file.
	 */
    static void writeToFile();

};

#endif // DATAMANAGER_H
