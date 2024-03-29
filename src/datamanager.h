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

#include <QString>
#include <QSettings>

class Cadet;
class InspectionCard;
class SupplyItem;
class MainWindow;
class Item;

class QJsonObject;

/**
 * @brief An interface between the program and the files that store the data for this application.
 */
class DataManager {

public:

	/**
	 * @brief All the cadets that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, Cadet> cadets;
	/**
	 * @brief All the supply items that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, SupplyItem> supplyItems;
	/**
	 * @brief All the inspection logs that have been entered into the program, indexed by their UUID.
	 */
	static QMap<QString, InspectionCard> insCards;
	/**
	 * @brief Supply item categories that were found from loaded items.
	 */
	static QSet<QString> supplyCategories;
	/**
	 * @brief Any type of tracked item indexed by their UUID.
	 */
	static QMap<QString, Item> items;

	/**
	 * @brief Reads all data from a QJsonObject and loads it into memory.
	 * @param The JSON file, converted into a QJsonObject.
	 */
	static void read(QJsonObject json);
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
	 * @brief Converts a JSON file at the given path to a QJsonObject and then stores it.
	 */
	static void readFromFile(const QString filePath);
	/**
	 * @brief Writes stored data out to a JSON file.
	 */
	static void writeToFile();
	/**
	 * @brief Writes stored data to given path.
	 */
	static void writeToFile(const QString filePath);

	static void newFile();

	static void setMainWindow(MainWindow *value);

	static void setDirty();

	static QString getFilePath();

private:

	QSettings settings;

	static MainWindow *mainWindow;

	static QString filePath;

};

#endif // DATAMANAGER_H
