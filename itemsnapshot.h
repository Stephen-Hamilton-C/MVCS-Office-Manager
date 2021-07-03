/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef ITEMSNAPSHOT_H
#define ITEMSNAPSHOT_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

class ItemSnapshot
{
public:
	ItemSnapshot();
	ItemSnapshot(QString objectUUID, QString uuid, QMap<QString, QVariant> properties, QDate date);

	/**
	 * @brief The UUID of the Item this goes to
	 */
	QString itemUUID;
	QString uuid;
	QMap<QString, QVariant> properties;
	QDate date;

	/**
	 * @brief Sets all variables to values read from the QJsonObject, if they exist, supplied by the `DataManager`.
	 * @param A reference to a QJsonObject read from a file.
	 */
	void read(const QJsonObject &json);
	/**
	 * @brief Writes all variables to a QJsonObject to be written to a file later by the `DataManager`.
	 * @param A reference to a QJsonObject that is to be written to a file.
	 */
	void write(QJsonObject &json);
};

#endif // ITEMSNAPSHOT_H
