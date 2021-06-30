#include "change.h"
#include "uuidgenerator.h"

#include <QJsonArray>

Change::Change()
{

}

void Change::read(const QJsonObject &json)
{
    if(json.contains("change_objectUUID") && json["change_objectUUID"].isString()){
        objectUUID = json["change_objectUUID"].toString();
    }

    if(json.contains("change_uuid") && json["change_uuid"].isString()){
        uuid = json["change_uuid"].toString();
    } else {
        uuid = UUIDGenerator::generateUUID(UUIDGenerator::CHANGE);
    }

    if(json.contains("change_property") && json["change_property"].isString()){
        property = json["change_property"].toString();
    }

    if(json.contains("change_value")){
        value = json["change_value"].toVariant();
    }

    if(json.contains("change_date") && json["change_date"].isArray()){
        //Year, Month, Day
        QJsonArray dateArray = json["card_date"].toArray();
        date = QDate(dateArray[0].toInt(), dateArray[1].toInt(), dateArray[2].toInt());
    }
}

void Change::write(QJsonObject &json)
{
    json["change_objectUUID"] = objectUUID;
    json["change_uuid"] = uuid;
    json["change_property"] = property;
    json["change_value"] = value.toJsonObject();

    //Convert the QDate into a year, month, day array
    QJsonArray dateArray { date.year(), date.month(), date.day() };
    json["change_date"] = dateArray;
}
