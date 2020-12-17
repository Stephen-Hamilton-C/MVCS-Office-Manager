#include "cadet.h"
#include "datamanager.h"

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
    switch(rank){
        case RANK::BASIC:
            return "Airman Basic";
        case RANK::AMN:
            return "Airman";
        case RANK::A1C:
            return "Airman 1st Class";
        case RANK::SRA:
            return "Senior Airman";
        case RANK::SSGT:
            return "Staff Sergeant";
        case RANK::TSGT:
            return "Technical Sergeant";
        case RANK::MSGT:
            return "Master Sergeant";
        case RANK::SMSGT:
            return "Senior Master Sergeant";
        case RANK::CMSGT:
            return "Chief Master Sergeant";
        case RANK::LT2ND:
            return "2nd Lieutenant";
        case RANK::LT1ST:
            return "1st Lieutenant";
        case RANK::CAPT:
            return "Captain";
        case RANK::MAJ:
            return "Major";
        case RANK::LTCOL:
            return "Lieutenant Colonel";
        case RANK::COL:
            return "Colonel";
        case RANK::SM:
            return "Senior Member";
        case RANK::FO:
            return "Flight Officer";
        case RANK::TFO:
            return "Technical Flight Officer";
        case RANK::SFO:
            return "Senior Flight Officer";
        case RANK::BRIGGEN:
            return "Brigadier General";
        case RANK::MAJGEN:
            return "Major General";
		default:
			return "Visitor";
    }
}

QString Cadet::getRankStr() const{
    return getRankStr(this->rank);
}

QString Cadet::getShortRankStr(RANK rank) {
    switch(rank){
        case RANK::BASIC:
            return "BASIC";
        case RANK::AMN:
            return "Amn";
        case RANK::A1C:
            return "A1C";
        case RANK::SRA:
            return "SrA";
        case RANK::SSGT:
            return "SSgt";
        case RANK::TSGT:
            return "TSgt";
        case RANK::MSGT:
            return "MSgt";
        case RANK::SMSGT:
            return "SMSgt";
        case RANK::CMSGT:
            return "CMSgt";
        case RANK::LT2ND:
            return "2Lt";
        case RANK::LT1ST:
            return "1Lt";
        case RANK::CAPT:
            return "Capt";
        case RANK::MAJ:
            return "Maj";
        case RANK::LTCOL:
            return "LtCol";
        case RANK::COL:
            return "Col";
        case RANK::SM:
            return "SM";
        case RANK::FO:
            return "FO";
        case RANK::TFO:
            return "TFO";
        case RANK::SFO:
            return "SFO";
        case RANK::BRIGGEN:
            return "BrigGen";
        case RANK::MAJGEN:
            return "MajGen";
		default:
			return "Visitor";
    }
}

QString Cadet::getShortRankStr() const{
    return getShortRankStr(this->rank);
}

QString Cadet::getFlightStr(FLIGHT flight) {
    switch (flight) {
        case FLIGHT::ALPHA:
            return "Alpha";
        case FLIGHT::BRAVO:
            return "Bravo";
        case FLIGHT::CHARLIE:
            return "Charlie";
        case FLIGHT::DELTA:
            return "Delta";
        case FLIGHT::ECHO:
            return "Echo";
        case FLIGHT::FOXTROT:
            return "Foxtrot";
        case FLIGHT::GOLF:
            return "Golf";
        case FLIGHT::HOTEL:
            return "Hotel";
        case FLIGHT::INDIA:
            return "India";
        case FLIGHT::JULIET:
            return "Juliet";
        case FLIGHT::KILO:
            return "Kilo";
        case FLIGHT::LIMA:
            return "Lima";
        case FLIGHT::MIKE:
            return "Mike";
        case FLIGHT::NOVEMBER:
            return "November";
        case FLIGHT::OSCAR:
            return "Oscar";
        case FLIGHT::PAPA:
            return "Papa";
        case FLIGHT::QUEBEC:
            return "Quebec";
        case FLIGHT::ROMEO:
            return "Romeo";
        case FLIGHT::SIERRA:
            return "Sierra";
        case FLIGHT::TANGO:
            return "Tango";
        case FLIGHT::UNIFORM:
            return "Uniform";
        case FLIGHT::VICTOR:
            return "Victor";
        case FLIGHT::WHISKEY:
            return "Whiskey";
        case FLIGHT::XRAY:
            return "X-Ray";
        case FLIGHT::YANKEE:
            return "Yankee";
        case FLIGHT::ZULU:
            return "Zulu";
        case FLIGHT::TRAINING:
            return "Training";
        case FLIGHT::STAFF:
            return "Staff";
		default:
            return "Unassigned";
    }
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
			return firstName+" "+lastName;
		case NAMEFORMAT::GRADEFIRSTLAST:
			return getShortGradeStr()+getShortRankStr()+" "+getFormattedName(NAMEFORMAT::FIRSTLAST);
		case NAMEFORMAT::GRADELASTFIRST:
			return getShortGradeStr()+getShortRankStr()+" "+getFormattedName(NAMEFORMAT::LASTFIRST);
		default: //NAMEFORMAT::LASTFIRST
			return lastName+", "+firstName;
    }
}

void Cadet::read(const QJsonObject& json) {
	//All of these if statements are to check if the value actually exists in file.

	//If a UUID is not found, generate one.
	//Setting it to the object will do nothing as the DataManager won't write to file if this function is being called
	if(json.contains("cadet_uuid") && json["cadet_uuid"].isString()){
		uuid = json["cadet_uuid"].toString();
	} else {
		uuid = QUuid::createUuid().toString();
	}

    if(json.contains("cadet_capid") && json["cadet_capid"].isDouble()){
        capid = json["cadet_capid"].toInt();
    }

    if(json.contains("cadet_grade") && json["cadet_grade"].isDouble()){
        grade = GRADE(json["cadet_grade"].toInt());
    }

    if(json.contains("cadet_rank") && json["cadet_rank"].isDouble()){
        rank = RANK(json["cadet_rank"].toInt());
    }

	if(json.contains("cadet_firstName") && json["cadet_firstName"].isString()){
        firstName = json["cadet_firstName"].toString();
    }

	if(json.contains("cadet_lastName") && json["cadet_lastName"].isString()){
        lastName = json["cadet_lastName"].toString();
    }

    if(json.contains("cadet_flight") && json["cadet_flight"].isDouble()){
        flight = FLIGHT(json["cadet_flight"].toInt());
    }

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

int Cadet::getPhase() const{
    if(rank == RANK::AMN || rank == RANK::A1C || rank == RANK::SRA){
        return 1;
    } else if(rank == RANK::SSGT || rank == RANK::TSGT || rank == RANK::MSGT || rank == RANK::SMSGT || rank == RANK::CMSGT){
        return 2;
    } else if(rank == RANK::LT2ND || rank == RANK::LT1ST){
        return 3;
    } else if(rank == RANK::CAPT || rank == RANK::MAJ || rank == RANK::LTCOL || rank == RANK::COL){
        return 4;
    }
    return 1;
}

QString Cadet::toString() {
	return uuid+", "+QString::number(capid)+", "+getGradeStr(grade)+", "+getRankStr(rank)+", "+firstName+", "+lastName+", "+getFlightStr(flight)+", "+notes;
}
