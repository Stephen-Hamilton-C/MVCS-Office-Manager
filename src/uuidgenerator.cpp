/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "uuidgenerator.h"

#include "cadet.h"
#include "supplyitem.h"
#include "inspectioncard.h"

UUIDGenerator::UUIDGenerator()
{

}

QString UUIDGenerator::generateUUID(IDType idType, QString uuid)
{
	if(uuid.length() == 0){
		uuid = QUuid::createUuid().toString();
		removeBraces(uuid);
    } else if(uuid.at(0) == '{'){
		removeBraces(uuid);
	}

	switch (idType) {
		case IDType::STANDARD:
			return "manager::"+uuid;
		case IDType::CADET:
			return "manager::cadet::"+uuid;
		case IDType::SUPPLY:
			return "manager::item::"+uuid;
		case IDType::CARD:
			return "manager::card::"+uuid;
		case IDType::CHANGE:
			return "manager::change::"+uuid;
	}

	return uuid;
}

void UUIDGenerator::removeBraces(QString &uuid)
{
	uuid.remove(0, 1);
	uuid.remove(uuid.length()-1, 1);
}
