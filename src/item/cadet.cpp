/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "cadet.h"
#include "datamanager.h"
#include "uuidgenerator.h"
#include "changesmanager.h"

#include <QDebug>

QMap<Cadet::FLIGHT, QString> Cadet::_flightToStr {
	{FLIGHT::ALPHA, "Alpha"},
	{FLIGHT::BRAVO, "Bravo"},
	{FLIGHT::CHARLIE, "Charlie"},
	{FLIGHT::DELTA, "Delta"},
	{FLIGHT::ECHO, "Echo"},
	{FLIGHT::FOXTROT, "Foxtrot"},
	{FLIGHT::GOLF, "Golf"},
	{FLIGHT::HOTEL, "Hotel"},
	{FLIGHT::INDIA, "India"},
	{FLIGHT::JULIET, "Juliet"},
	{FLIGHT::KILO, "Kilo"},
	{FLIGHT::LIMA, "Lima"},
	{FLIGHT::MIKE, "Mike"},
	{FLIGHT::NOVEMBER, "November"},
	{FLIGHT::OSCAR, "Oscar"},
	{FLIGHT::PAPA, "Papa"},
	{FLIGHT::QUEBEC, "Quebec"},
	{FLIGHT::ROMEO, "Romeo"},
	{FLIGHT::SIERRA, "Sierra"},
	{FLIGHT::TANGO, "Tango"},
	{FLIGHT::UNIFORM, "Uniform"},
	{FLIGHT::VICTOR, "Victor"},
	{FLIGHT::WHISKEY, "Whiskey"},
	{FLIGHT::XRAY, "X-Ray"},
	{FLIGHT::YANKEE, "Yankee"},
	{FLIGHT::ZULU, "Zulu"},
	{FLIGHT::TRAINING, "Training"},
	{FLIGHT::STAFF, "Staff"},
	{FLIGHT::UNASSIGNED, "Unassigned"}
};

QMap<Cadet::RANK, QString> Cadet::_rankToStr {
	{RANK::BASIC, "Airman Basic"},
	{RANK::AMN, "Airman"},
	{RANK::A1C, "Airman 1st Class"},
	{RANK::SRA, "Senior Airman"},
	{RANK::SSGT, "Staff Sergeant"},
	{RANK::TSGT, "Technical Sergeant"},
	{RANK::MSGT, "Master Sergeant"},
	{RANK::SMSGT, "Senior Master Sergeant"},
	{RANK::CMSGT, "Chief Master Sergeant"},
	{RANK::LT2ND, "2nd Lieutenant"},
	{RANK::LT1ST, "1st Lieutenant"},
	{RANK::CAPT, "Captain"},
	{RANK::MAJ, "Major"},
	{RANK::LTCOL, "Lieutenant Colonel"},
	{RANK::COL, "Colonel"},
	{RANK::SM, "Senior Member"},
	{RANK::FO, "Flight Officer"},
	{RANK::TFO, "Technical Flight Officer"},
	{RANK::SFO, "Senior Flight Officer"},
	{RANK::BRIGGEN, "Brigadier General"},
	{RANK::MAJGEN, "Major General"},
	{RANK::VISITOR, "Visitor"}
};

QMap<Cadet::RANK, QString> Cadet::_rankToShortStr {
	{RANK::BASIC, "BASIC"},
	{RANK::AMN, "Amn"},
	{RANK::A1C, "A1C"},
	{RANK::SRA, "SrA"},
	{RANK::SSGT, "SSgt"},
	{RANK::TSGT, "TSgt"},
	{RANK::MSGT, "MSgt"},
	{RANK::SMSGT, "SMSgt"},
	{RANK::CMSGT, "CMSgt"},
	{RANK::LT2ND, "2Lt"},
	{RANK::LT1ST, "1Lt"},
	{RANK::CAPT, "Capt"},
	{RANK::MAJ, "Maj"},
	{RANK::LTCOL, "LtCol"},
	{RANK::COL, "Col"},
	{RANK::SM, "SM"},
	{RANK::FO, "FO"},
	{RANK::TFO, "TFO"},
	{RANK::SFO, "SFO"},
	{RANK::BRIGGEN, "BrigGen"},
	{RANK::MAJGEN, "MajGen"},
	{RANK::VISITOR, "Visitor"}
};

void Cadet::takeSnapshot()
{
	ChangesManager::createSnapshot(
				this->uuid,
				UUIDGenerator::generateUUID(UUIDGenerator::IDType::CHANGE),
				QMap<QString, QVariant>{
					{"grade", this->grade},
					{"rank", this->rank},
					{"flight", this->flight}
				},
				QDate::currentDate()
				);
}

Cadet::Cadet(QString uuid, int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes) {
	this->uuid = uuid;
	this->capid = capid;
	this->grade = grade;
	this->rank = rank;
	this->firstName = firstName;
	this->lastName = lastName;
	this->flight = flight;
	this->notes = notes;
	qDebug() << "Cadet created:\n" << toString();
}

Cadet::Cadet(){
	qDebug() << "Empty Cadet created.";
}

QString Cadet::getRankStr(RANK rank) {
	return _rankToStr[rank];
}

QString Cadet::getRankStr() const {
	return getRankStr(this->rank);
}

QString Cadet::getShortRankStr(RANK rank) {
	return _rankToShortStr[rank];
}

QString Cadet::getShortRankStr() const{
	return getShortRankStr(this->rank);
}

QString Cadet::getFlightStr(FLIGHT flight) {
	return _flightToStr[flight];
}

QString Cadet::getFlightStr() const{
	return getFlightStr(this->flight);
}

QString Cadet::getGradeStr(GRADE grade){
	switch (grade) {
		case GRADE::CADET:
			return "Cadet";
		case GRADE::SENIORMEMBER:
			return "Senior Member";
		default:
			return "N/A";
	}
}

QString Cadet::getGradeStr() const{
	return getGradeStr(this->grade);
}

QString Cadet::getShortGradeStr(GRADE grade, bool slash) {
	switch (grade) {
		case GRADE::CADET:
			return slash ? "C/" : "C";
		case GRADE::SENIORMEMBER:
			return slash ? "SM/" : "SM";
		default:
			return "N/A";
	}
}

QString Cadet::getShortGradeStr(bool slash) const{
	return getShortGradeStr(this->grade, slash);
}

QString Cadet::getFormattedName(NAMEFORMAT format) const{
	switch (format) {
		case NAMEFORMAT::FIRSTLAST:
			return firstName.length() != 0 ? firstName+" "+lastName : lastName;
		case NAMEFORMAT::GRADEFIRSTLAST:
			return getShortGradeStr()+getShortRankStr()+" "+getFormattedName(NAMEFORMAT::FIRSTLAST);
		case NAMEFORMAT::GRADELASTFIRST:
			return getShortGradeStr()+getShortRankStr()+" "+getFormattedName(NAMEFORMAT::LASTFIRST);
		default: //NAMEFORMAT::LASTFIRST
			return firstName.length() != 0 ? lastName+", "+firstName : lastName;
	}
}

void Cadet::read(const QJsonObject& json) {
	//All of these if statements are to check if the value actually exists in file.

	//If a UUID is not found, generate one.
	//Setting it to the object will do nothing as the DataManager won't write to file if this function is being called
	if(json.contains("cadet_uuid") && json["cadet_uuid"].isString()){
		uuid = json["cadet_uuid"].toString();
	} else {
		uuid = UUIDGenerator::generateUUID(UUIDGenerator::CADET);
	}

	//CAP ID
	if(json.contains("cadet_capid") && json["cadet_capid"].isDouble()){
		capid = json["cadet_capid"].toInt();
	}

	//Grade
	if(json.contains("cadet_grade") && json["cadet_grade"].isDouble()){
		grade = GRADE(json["cadet_grade"].toInt());
	}

	//Rank
	if(json.contains("cadet_rank") && json["cadet_rank"].isDouble()){
		rank = RANK(json["cadet_rank"].toInt());
	}

	//First name
	if(json.contains("cadet_firstName") && json["cadet_firstName"].isString()){
		firstName = json["cadet_firstName"].toString();
	}

	//Last name
	if(json.contains("cadet_lastName") && json["cadet_lastName"].isString()){
		lastName = json["cadet_lastName"].toString();
	}

	//Flight
	if(json.contains("cadet_flight") && json["cadet_flight"].isDouble()){
		flight = FLIGHT(json["cadet_flight"].toInt());
	}

	//Notes
	if(json.contains("cadet_notes") && json["cadet_notes"].isString()){
		notes = json["cadet_notes"].toString();
	}
}

void Cadet::write(QJsonObject& json) const {
	json["cadet_uuid"] = uuid;
	json["cadet_capid"] = capid;
	json["cadet_grade"] = grade;
	json["cadet_rank"] = rank;
	json["cadet_firstName"] = firstName;
	json["cadet_lastName"] = lastName;
	json["cadet_flight"] = flight;
	json["cadet_notes"] = notes;
}

int Cadet::getPhase() const {
	if(rank == RANK::BASIC || rank == RANK::AMN || rank == RANK::A1C || rank == RANK::SRA){
		//Phase 1: BASIC - SrA
		return 1;
	} else if(rank == RANK::SSGT || rank == RANK::TSGT || rank == RANK::MSGT || rank == RANK::SMSGT || rank == RANK::CMSGT){
		//Phase 2: SSgt - CMSgt
		return 2;
	} else if(rank == RANK::LT2ND || rank == RANK::LT1ST){
		//Phase 3: 2Lt - 1Lt
		return 3;
	} else if(rank == RANK::CAPT || rank == RANK::MAJ || rank == RANK::LTCOL || rank == RANK::COL){
		//Phase 4: Capt - Col
		return 4;
	}
	return 1;
}

QString Cadet::toString() {
	//UUID, CAP ID, Grade, Rank, First name, Last name, Flight, Notes
	return uuid+", "+QString::number(capid)+", "+getGradeStr(grade)+", "+getRankStr(rank)+", "+firstName+", "+lastName+", "+getFlightStr(flight)+", "+notes;
}
