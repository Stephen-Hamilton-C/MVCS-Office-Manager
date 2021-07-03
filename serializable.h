/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#endif // SERIALIZABLE_H

#include <QJsonObject>

class Serializable {
public:
	/**
	 * @brief Sets all variables to values read from the QJsonObject, if they exist, supplied by the `DataManager`.
	 * @param A reference to a QJsonObject read from a file.
	 */
	virtual void read(const QJsonObject& json) = 0;
	/**
	 * @brief Writes all variables to a QJsonObject to be written to a file later by the `DataManager`.
	 * @param A reference to a QJsonObject that is to be written to a file.
	 */
	virtual void write(QJsonObject& json) const = 0;
};
