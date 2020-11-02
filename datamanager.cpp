#include "datamanager.h"

QMap<int, Cadet*> DataManager::cadets = QMap<int, Cadet*>();
QMap<QString, SupplyItem*> DataManager::items = QMap<QString, SupplyItem*>();
QMap<int, InspectionCard*> DataManager::insCards = QMap<int, InspectionCard*>();

DataManager::DataManager() {

}

void DataManager::read(const QJsonObject &json){
    if(json.contains("cadets") && json["cadets"].isArray()){
        cadets.clear();
        for(auto cadet : json["cadets"].toArray()){
            Cadet newCadet;
            newCadet.read(cadet.toObject());
            cadets.insert(newCadet.capid, &newCadet);
        }
    }

    if(json.contains("supplyitems") && json["supplyitems"].isArray()){
        items.clear();
        for(auto item : json["supplyitems"].toArray()){
            SupplyItem newItem;
            newItem.read(item.toObject());
            items.insert(newItem.name, &newItem);
        }
    }

    if(json.contains("inspectioncards") && json["inspectioncards"].isArray()){
        insCards.clear();
        for(auto card : json["inspectioncards"].toArray()){
            InspectionCard newCard;
            newCard.read(card.toObject());
            insCards.insert(newCard.cadetID, &newCard);
        }
    }
}

void DataManager::write(QJsonObject &json) const {
    QJsonArray jCadets;
    auto iCadets = QMapIterator<int, Cadet*>(cadets);
    while(iCadets.hasNext()){
        iCadets.next();
        QJsonObject cadetJson;
        iCadets.value()->write(cadetJson);
        jCadets.append(cadetJson);
    }
    json["cadets"] = jCadets;

    QJsonArray jItems;
    auto iItems = QMapIterator<QString, SupplyItem*>(items);
    while(iItems.hasNext()){
        iItems.next();
        QJsonObject itemJson;
        iItems.value()->write(itemJson);
        jItems.append(itemJson);
    }
    json["supplyitems"] = jItems;

    QJsonArray jCards;
    auto iCards = QMapIterator<int, InspectionCard*>(insCards);
    while(iCards.hasNext()){
        iCards.next();
        QJsonObject cardJson;
        iCards.value()->write(cardJson);
        jCards.append(cardJson);
    }
    json["inspectioncards"] = jCards;
}
