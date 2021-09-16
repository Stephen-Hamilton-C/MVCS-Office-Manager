/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef UUIDGENERATOR_H
#define UUIDGENERATOR_H

#include <QUuid>

class UUIDGenerator
{
public:
	UUIDGenerator();

	enum IDType {
		STANDARD,
		CADET,
		SUPPLY,
		CARD,
		CHANGE
	};

	static QString generateUUID(IDType idType = IDType::STANDARD, QString uuid = "");

private:

	static void removeBraces(QString &uuid);

};

#endif // UUIDGENERATOR_H
