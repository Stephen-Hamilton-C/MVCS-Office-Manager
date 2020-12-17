/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "datamanager.h"
#include "constants.h"

QMap<QString, Cadet> DataManager::cadets = QMap<QString, Cadet>();
QMap<QString, SupplyItem> DataManager::items = QMap<QString, SupplyItem>();
QMap<QString, InspectionCard> DataManager::insCards = QMap<QString, InspectionCard>();

DataManager::DataManager() {

}

void DataManager::read(const QJsonObject &json){

    if(json.contains("cadets") && json["cadets"].isArray()){
		//Read cadets array and store each cadet
        cadets.clear();
        for(auto cadet : json["cadets"].toArray()){
            Cadet newCadet;
            newCadet.read(cadet.toObject());
			cadets.insert(newCadet.uuid, newCadet);
			qDebug() << "Cadet Read:" << newCadet.toString();
        }
    }

    if(json.contains("supplyitems") && json["supplyitems"].isArray()){
		//Read supply items array and store each item
        items.clear();
        for(auto item : json["supplyitems"].toArray()){
            SupplyItem newItem;
            newItem.read(item.toObject());
			items.insert(newItem.uuid, newItem);
			qDebug() << "Supply Item Read:" << newItem.toString();
        }
    }

    if(json.contains("inspectioncards") && json["inspectioncards"].isArray()){
		//Read inspection logs array and store each log
        insCards.clear();
        for(auto card : json["inspectioncards"].toArray()){
            InspectionCard newCard;
            newCard.read(card.toObject());
			insCards.insert(newCard.uuid, newCard);
			qDebug() << "Inspection Log Entry Read:" << newCard.toString();
        }
    }

}

void DataManager::write(QJsonObject &json) {

	//Convert cadets to a QJsonObject
    QJsonArray jCadets;
	auto iCadets = QMapIterator<QString, Cadet>(cadets);
    while(iCadets.hasNext()){
        iCadets.next();
        QJsonObject cadetJson;
		iCadets.value().write(cadetJson);
        jCadets.append(cadetJson);
    }
	//Set the QJsonObject to the main QJsonObject that will be written to file
    json["cadets"] = jCadets;

	//Convert items to a QJsonObject
    QJsonArray jItems;
	auto iItems = QMapIterator<QString, SupplyItem>(items);
    while(iItems.hasNext()){
        iItems.next();
        QJsonObject itemJson;
		iItems.value().write(itemJson);
        jItems.append(itemJson);
    }
	//Set the QJsonObject to the main QJsonObject that will be written to file
    json["supplyitems"] = jItems;

	//Convert inspection logs to a QJsonObject
    QJsonArray jCards;
	auto iCards = QMapIterator<QString, InspectionCard>(insCards);
    while(iCards.hasNext()){
        iCards.next();
        QJsonObject cardJson;
		iCards.value().write(cardJson);
        jCards.append(cardJson);
    }
	//Set the QJsonObject to the main QJsonObject that will be written to file
    json["inspectioncards"] = jCards;

}

void DataManager::readFromFile() {

	//Prepare to write to file
	QFile loadFile(Constants::defaultSaveFileName);

    if(loadFile.open(QIODevice::ReadOnly)){
		//Load it into a QJsonDocemunt and read
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        read(loadDoc.object());
    }

}

void DataManager::writeToFile() {

	//Prepare to save to file
	QFile saveFile(Constants::defaultSaveFileName);

    if(saveFile.open(QIODevice::WriteOnly)){
		//Load data into a QJsonDocument and write the raw JSON to file
        QJsonObject saveObject;
        write(saveObject);
        saveFile.write(QJsonDocument(saveObject).toJson());
    } else {
		//TODO: Make an error dialog
    }

}
