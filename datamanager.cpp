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
#include "supplyitem.h"
#include "inspectioncard.h"
#include "mainwindow.h"
#include "dataconverter.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include <QStandardPaths>

//Initialize static vars
QMap<QString, Cadet> DataManager::cadets = QMap<QString, Cadet>();
QMap<QString, SupplyItem> DataManager::supplyItems = QMap<QString, SupplyItem>();
QMap<QString, InspectionCard> DataManager::insCards = QMap<QString, InspectionCard>();
QSet<QString> DataManager::itemCategories = QSet<QString>();
QString DataManager::filePath = "";
MainWindow *DataManager::mainWindow = nullptr;

void DataManager::read(QJsonObject json){

    if(!json.contains("version")){
        json["version"] = 0;
    }

    while(json["version"].toInt() < Constants::jsonVersion){
        DataConverter::convert(json);
    }

    //Cadets
    if(json.contains("cadets") && json["cadets"].isArray()){
        //Read cadets array and store each cadet
        cadets.clear();
        for(int i = 0; i < json["cadets"].toArray().count(); i++){
            auto cadet = json["cadets"].toArray()[i];
            Cadet newCadet;
            newCadet.read(cadet.toObject());
            cadets.insert(newCadet.uuid, newCadet);
            qDebug() << "Cadet Read:" << newCadet.toString();
        }
    }

    //Supply items
    if(json.contains("supplyitems") && json["supplyitems"].isArray()){
        //Read supply items array and store each item
        supplyItems.clear();
        for(int i = 0; i < json["supplyitems"].toArray().count(); i++){
            auto item = json["supplyitems"].toArray()[i];
            SupplyItem newItem;
            newItem.read(item.toObject());
            supplyItems.insert(newItem.uuid, newItem);
            qDebug() << "Supply Item Read:" << newItem.toString();

            //Populate item categories
            if(!newItem.category.isEmpty() && !itemCategories.contains(newItem.category)){
                itemCategories.insert(newItem.category);
            }
        }
    }

    //Inspection cards
    if(json.contains("inspectioncards") && json["inspectioncards"].isArray()){
        //Read inspection logs array and store each log
        insCards.clear();
        for(int i = 0; i < json["inspectioncards"].toArray().count(); i++){
            auto card = json["inspectioncards"].toArray()[i];
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
    auto iItems = QMapIterator<QString, SupplyItem>(supplyItems);
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

    json["version"] = Constants::jsonVersion;
}

void DataManager::readFromFile() {

    mainWindow->showStatusMessage("Loading...");

    //Prepare to write to file
    QFile loadFile(filePath);

    if(loadFile.open(QIODevice::ReadOnly)){
        //Load it into a QJsonDocemunt and read
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        read(loadDoc.object());

        mainWindow->showStatusMessage("Loaded from "+filePath);
    } else {
        QMessageBox::critical(mainWindow, "Unable to open", "An error occurred while trying to open file "+filePath);
        mainWindow->showStatusMessage("Error occurred while opening file "+filePath);
    }

}

void DataManager::writeToFile() {

    mainWindow->showStatusMessage("Saving...");

    if(filePath.length() == 0){
        mainWindow->on_actionSave_as_triggered();
        return;
    }

    //Prepare to save to file
    QFile saveFile(filePath);

    if(saveFile.open(QIODevice::WriteOnly)){
        //Load data into a QJsonDocument and write the raw JSON to file
        QJsonObject saveObject;
        write(saveObject);
        saveFile.write(QJsonDocument(saveObject).toJson());

        mainWindow->showStatusMessage("Saved to "+filePath);
        mainWindow->setDirty(false);
    } else {
        mainWindow->on_actionSave_as_triggered();
        return;
    }

}

void DataManager::newFile(){
    filePath = "";
    cadets.clear();
    supplyItems.clear();
    insCards.clear();
    itemCategories.clear();
}

void DataManager::setMainWindow(MainWindow *value)
{
    mainWindow = value;
}

void DataManager::setDirty()
{
    mainWindow->setDirty(true);
}
