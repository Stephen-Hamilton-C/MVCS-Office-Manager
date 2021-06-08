#include "dataconverter.h"
#include "datamanager.h"
#include "constants.h"
#include "uuidgenerator.h"

#include <QJsonArray>

//MAKE A UUID GENERATOR

DataConverter::DataConverter()
{

}

//TODO: Completely redesign this thing oml
void DataConverter::convert(QJsonObject &json)
{
    int jsonVersion = 0;

    if(json.contains("version") && json["version"].isDouble()){
        jsonVersion = json["version"].toInt();
    }

    if(jsonVersion >= Constants::jsonVersion)
        return;

    switch(jsonVersion){
        case 0: {
            //Update to new UUID pattern

            if(json.contains("cadets") && json["cadets"].isArray()){
                QJsonArray cadets = json["cadets"].toArray();
                for(int i = 0; i < cadets.count(); i++){
                    QJsonObject cadet = cadets[i].toObject();
                    if(cadet.contains("cadet_uuid") && cadet["cadet_uuid"].isString()){
                        QString uuid = cadet["cadet_uuid"].toString();
                        uuid = UUIDGenerator::generateUUID(UUIDGenerator::CADET, uuid);

                        cadet["cadet_uuid"] = uuid;
                    }

                    cadets[i] = cadet;
                }

                json["cadets"] = cadets;
            }

            if(json.contains("supplyitems") && json["supplyitems"].isArray()){
                QJsonArray items = json["supplyitems"].toArray();
                for(int i = 0; i < items.count(); i++){
                    QJsonObject item = items[i].toObject();
                    if(item.contains("item_uuid") && item["item_uuid"].isString()){
                        QString uuid = item["item_uuid"].toString();
                        uuid = UUIDGenerator::generateUUID(UUIDGenerator::ITEM, uuid);

                        item["item_uuid"] = uuid;
                    }

                    items[i] = item;
                }

                json["supplyitems"] = items;
            }

            if(json.contains("inspectioncards") && json["inspectioncards"].isArray()){
                QJsonArray cards = json["inspectioncards"].toArray();
                for(int i = 0; i < cards.count(); i++){
                    QJsonObject card = cards[i].toObject();
                    if(card.contains("card_uuid") && card["card_uuid"].isString()){
                        QString uuid = card["card_uuid"].toString();
                        uuid = UUIDGenerator::generateUUID(UUIDGenerator::CARD, uuid);

                        card["card_uuid"] = uuid;
                    }

                    if(card.contains("card_cadetUUID") && card["card_cadetUUID"].isString()){
                        QString uuid = card["card_cadetUUID"].toString();
                        uuid = UUIDGenerator::generateUUID(UUIDGenerator::CADET, uuid);

                        card["card_cadetUUID"] = uuid;
                    }

                    cards[i] = card;
                }

                json["inspectioncards"] = cards;
            }
            break;
        }
    }

    jsonVersion++;
    json["version"] = jsonVersion;
}
