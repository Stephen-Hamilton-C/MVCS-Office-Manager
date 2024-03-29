﻿/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "inspectioncard.h"
#include "datamanager.h"
#include "uuidgenerator.h"

#include <QJsonArray>
#include <QDebug>

InspectionCard::InspectionCard() {
	qDebug() << "Creating empty Inspection Card";
}

void InspectionCard::takeSnapshot()
{
	qDebug() << "Inspection logs should not change";
}

InspectionCard::InspectionCard(QString uuid, QString cadetUUID, QDate date,
							   RATING appearanceScore, RATING garmentsScore, RATING accountrementsScore, RATING footwearScore, RATING bearingScore) {
	this->uuid = uuid;
	this->cadetUUID = cadetUUID;
	this->date = date;
	this->appearanceScore = appearanceScore;
	this->garmentsScore = garmentsScore;
	this->accountrementsScore = accountrementsScore;
	this->footwearScore = footwearScore;
	this->bearingScore = bearingScore;

	Cadet* cadet = getCadet();
	this->cadetPhaseAtInspect = cadet->getPhase();
	this->cadetFlightAtInspect = cadet->flight;
}

int InspectionCard::getTotalPoints() const {
	return appearanceScore + garmentsScore + accountrementsScore + footwearScore + bearingScore;
}

InspectionCard::RATING InspectionCard::getOverallRating() const {
	int overallPoints = getTotalPoints();
	//If in the learning phase, points are more lenient
	if(cadetPhaseAtInspect == 1){
		if(overallPoints <= 3){
			return RATING::NEEDSIMPROVEMENT;
		} else if(overallPoints == 4 || overallPoints == 5){
			return RATING::SATISFACTORY;
		} else {
			return RATING::EXCELLENT;
		}
	} else {
		if(overallPoints <= 4){
			return RATING::NEEDSIMPROVEMENT;
		} else if(overallPoints >= 5 && overallPoints <= 7){
			return RATING::SATISFACTORY;
		} else {
			return RATING::EXCELLENT;
		}
	}
}

QString InspectionCard::getRatingString(int score) const {
	switch(score){
		case 0:
			return "0 - Needs Improvement";
		case 1:
			return "1 - Satisfactory";
		case 2:
			return "2 - Excellent";
		default:
			return "N/A";
	}
}

QString InspectionCard::getRatingString(RATING rating) const {
	return getRatingString((int)rating);
}

Cadet* InspectionCard::getCadet() const {
	return &DataManager::cadets[cadetUUID];
}

void InspectionCard::read(const QJsonObject& json){
	//All of these if statements are to check if the value actually exists in file.

	//If a UUID is not found, generate one.
	//Setting it to the object will do nothing as the DataManager won't write to file if this function is being called
	if(json.contains("card_uuid") && json["card_uuid"].isString()){
		uuid = json["card_uuid"].toString();
	} else {
		uuid = UUIDGenerator::generateUUID(UUIDGenerator::CARD);
	}

	//UUID
	if(json.contains("card_cadetUUID") && json["card_cadetUUID"].isString()){
		cadetUUID = json["card_cadetUUID"].toString();
	}

	//Phase
	if(json.contains("card_cadetPhase") && json["card_cadetPhase"].isDouble()){
		cadetPhaseAtInspect = json["card_cadetPhase"].toInt();
	}

	//Flight
	if(json.contains("card_cadetFlight") && json["card_cadetFlight"].isDouble()){
		cadetFlightAtInspect = Cadet::FLIGHT(json["card_cadetFlight"].toInt());
	}

	//Date
	if(json.contains("card_date") && json["card_date"].isArray()){
		//Year, Month, Day
		QJsonArray dateArray = json["card_date"].toArray();
		date = QDate(dateArray[0].toInt(), dateArray[1].toInt(), dateArray[2].toInt());
	}

	//Appearance Score
	if(json.contains("card_appearanceScore") && json["card_appearanceScore"].isDouble()){
	   appearanceScore = RATING(json["card_appearanceScore"].toInt());
	}

	//Garments Score
	if(json.contains("card_garmentsScore") && json["card_garmentsScore"].isDouble()){
		garmentsScore = RATING(json["card_garmentsScore"].toInt());
	}

	//Accountrements Score
	if(json.contains("card_accountrementsScore") && json["card_accountrementsScore"].isDouble()){
		accountrementsScore = RATING(json["card_accountrementsScore"].toInt());
	}

	//Footwear Score
	if(json.contains("card_footwearScore") && json["card_footwearScore"].isDouble()){
		footwearScore = RATING(json["card_footwearScore"].toInt());
	}

	//Bearing Score
	if(json.contains("card_bearingScore") && json["card_bearingScore"].isDouble()){
		bearingScore = RATING(json["card_bearingScore"].toInt());
	}
}

void InspectionCard::write(QJsonObject &json) const {
	json["card_uuid"] = uuid;
	json["card_cadetUUID"] = cadetUUID;
	json["card_cadetPhase"] = cadetPhaseAtInspect;
	json["card_cadetFlight"] = cadetFlightAtInspect;

	//Convert the QDate into a year, month, day array
	QJsonArray dateArray { date.year(), date.month(), date.day() };
	json["card_date"] = dateArray;

	json["card_appearanceScore"] = appearanceScore;
	json["card_garmentsScore"] = garmentsScore;
	json["card_accountrementsScore"] = accountrementsScore;
	json["card_footwearScore"] = footwearScore;
	json["card_bearingScore"] = bearingScore;

}

QString InspectionCard::toString(){
	//UUID, name, appearance, garments, accountrements, footwear, bearing, total, overall
	return  uuid+", "+cadetUUID+" ("+getCadet()->getFormattedName()+"), "+QString::number(appearanceScore)
			+", "+QString::number(garmentsScore)+", "+QString::number(accountrementsScore)
			+", "+QString::number(footwearScore)+", "+QString::number(bearingScore)
			+", "+QString::number(getTotalPoints())+", "+QString::number(getOverallRating());
}
