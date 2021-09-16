/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "itemsnapshot.h"
#include "uuidgenerator.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>

ItemSnapshot::ItemSnapshot()
{

}

ItemSnapshot::ItemSnapshot(QString objectUUID, QString uuid, QMap<QString, QVariant> properties, QDate date)
{
	this->itemUUID = objectUUID;
	this->uuid = uuid;
	this->properties = properties;
	this->date = date;
}

void ItemSnapshot::read(const QJsonObject &json)
{
	if(json.contains("itemsnapshot_objectUUID") && json["itemsnapshot_objectUUID"].isString()){
		itemUUID = json["itemsnapshot_objectUUID"].toString();
	}

	if(json.contains("itemsnapshot_uuid") && json["itemsnapshot_uuid"].isString()){
		uuid = json["itemsnapshot_uuid"].toString();
	} else {
		uuid = UUIDGenerator::generateUUID(UUIDGenerator::CHANGE);
	}

	if(json.contains("itemsnapshot_properties")){
		properties = json["itemsnapshot_properties"].toVariant().toMap();
	}

	if(json.contains("itemsnapshot_date") && json["itemsnapshot_date"].isArray()){
		//Year, Month, Day
		QJsonArray dateArray = json["itemsnapshot_date"].toArray();
		date = QDate(dateArray[0].toInt(), dateArray[1].toInt(), dateArray[2].toInt());
	}
}

void ItemSnapshot::write(QJsonObject &json)
{
	json["itemsnapshot_objectUUID"] = itemUUID;
	json["itemsnapshot_uuid"] = uuid;
	//QMap<QString, QVariant> is considered a VariantMap since QString can be a QVariant
	json["itemsnapshot_properties"] = QJsonObject::fromVariantMap(properties);

	//Convert the QDate into a year, month, day array
	QJsonArray dateArray { date.year(), date.month(), date.day() };
	json["itemsnapshot_date"] = dateArray;
}
