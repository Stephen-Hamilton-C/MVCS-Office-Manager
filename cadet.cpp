#include "cadet.h"
#include "datamanager.h"

QStringList Cadet::tableHeader = QStringList() << "CapID" << "Grade" << "Rank" << "Name" << "Flight" << "Notes";
QMap<QString, Cadet::RANK> Cadet::comboBox_CadetRanks {
	{Cadet::getRankStr(Cadet::RANK::VISITOR), Cadet::RANK::VISITOR},
	{Cadet::getRankStr(Cadet::RANK::BASIC), Cadet::RANK::BASIC},
	{Cadet::getRankStr(Cadet::RANK::AMN), Cadet::RANK::AMN},
	{Cadet::getRankStr(Cadet::RANK::A1C), Cadet::RANK::A1C},
	{Cadet::getRankStr(Cadet::RANK::SRA), Cadet::RANK::SRA},
	{Cadet::getRankStr(Cadet::RANK::SSGT), Cadet::RANK::SSGT},
	{Cadet::getRankStr(Cadet::RANK::TSGT), Cadet::RANK::TSGT},
	{Cadet::getRankStr(Cadet::RANK::MSGT), Cadet::RANK::MSGT},
	{Cadet::getRankStr(Cadet::RANK::SMSGT), Cadet::RANK::SMSGT},
	{Cadet::getRankStr(Cadet::RANK::CMSGT), Cadet::RANK::CMSGT},
	{Cadet::getRankStr(Cadet::RANK::LT2ND), Cadet::RANK::LT2ND},
	{Cadet::getRankStr(Cadet::RANK::LT1ST), Cadet::RANK::LT1ST},
	{Cadet::getRankStr(Cadet::RANK::CAPT), Cadet::RANK::CAPT},
	{Cadet::getRankStr(Cadet::RANK::MAJ), Cadet::RANK::MAJ},
	{Cadet::getRankStr(Cadet::RANK::LTCOL), Cadet::RANK::LTCOL},
	{Cadet::getRankStr(Cadet::RANK::COL), Cadet::RANK::COL}
};
QMap<QString, Cadet::RANK> Cadet::comboBox_SMRanks {
	{Cadet::getRankStr(Cadet::RANK::VISITOR), Cadet::RANK::VISITOR},
	{Cadet::getRankStr(Cadet::RANK::SM), Cadet::RANK::SM},
	{Cadet::getRankStr(Cadet::RANK::FO), Cadet::RANK::FO},
	{Cadet::getRankStr(Cadet::RANK::TFO), Cadet::RANK::TFO},
	{Cadet::getRankStr(Cadet::RANK::SFO), Cadet::RANK::SFO},
	{Cadet::getRankStr(Cadet::RANK::LT2ND), Cadet::RANK::LT2ND},
	{Cadet::getRankStr(Cadet::RANK::LT1ST), Cadet::RANK::LT1ST},
	{Cadet::getRankStr(Cadet::RANK::CAPT), Cadet::RANK::CAPT},
	{Cadet::getRankStr(Cadet::RANK::MAJ), Cadet::RANK::MAJ},
	{Cadet::getRankStr(Cadet::RANK::LTCOL), Cadet::RANK::LTCOL},
	{Cadet::getRankStr(Cadet::RANK::COL), Cadet::RANK::COL},
	{Cadet::getRankStr(Cadet::RANK::BRIGGEN), Cadet::RANK::BRIGGEN},
	{Cadet::getRankStr(Cadet::RANK::MAJGEN), Cadet::RANK::MAJGEN}
};
QMap<QString, Cadet::FLIGHT> Cadet::comboBox_Flight {
	{Cadet::getFlightStr(Cadet::FLIGHT::UNASSIGNED), Cadet::FLIGHT::UNASSIGNED},
	{Cadet::getFlightStr(Cadet::FLIGHT::ALPHA), Cadet::FLIGHT::ALPHA},
	{Cadet::getFlightStr(Cadet::FLIGHT::BRAVO), Cadet::FLIGHT::BRAVO},
	{Cadet::getFlightStr(Cadet::FLIGHT::CHARLIE), Cadet::FLIGHT::CHARLIE},
	{Cadet::getFlightStr(Cadet::FLIGHT::DELTA), Cadet::FLIGHT::DELTA},
	{Cadet::getFlightStr(Cadet::FLIGHT::ECHO), Cadet::FLIGHT::ECHO},
	{Cadet::getFlightStr(Cadet::FLIGHT::FOXTROT), Cadet::FLIGHT::FOXTROT},
	{Cadet::getFlightStr(Cadet::FLIGHT::GOLF), Cadet::FLIGHT::GOLF},
	{Cadet::getFlightStr(Cadet::FLIGHT::HOTEL), Cadet::FLIGHT::HOTEL},
	{Cadet::getFlightStr(Cadet::FLIGHT::INDIA), Cadet::FLIGHT::INDIA},
	{Cadet::getFlightStr(Cadet::FLIGHT::JULIET), Cadet::FLIGHT::JULIET},
	{Cadet::getFlightStr(Cadet::FLIGHT::KILO), Cadet::FLIGHT::KILO},
	{Cadet::getFlightStr(Cadet::FLIGHT::LIMA), Cadet::FLIGHT::LIMA},
	{Cadet::getFlightStr(Cadet::FLIGHT::MIKE), Cadet::FLIGHT::MIKE},
	{Cadet::getFlightStr(Cadet::FLIGHT::NOVEMBER), Cadet::FLIGHT::NOVEMBER},
	{Cadet::getFlightStr(Cadet::FLIGHT::OSCAR), Cadet::FLIGHT::OSCAR},
	{Cadet::getFlightStr(Cadet::FLIGHT::PAPA), Cadet::FLIGHT::PAPA},
	{Cadet::getFlightStr(Cadet::FLIGHT::QUEBEC), Cadet::FLIGHT::QUEBEC},
	{Cadet::getFlightStr(Cadet::FLIGHT::ROMEO), Cadet::FLIGHT::ROMEO},
	{Cadet::getFlightStr(Cadet::FLIGHT::SIERRA), Cadet::FLIGHT::SIERRA},
	{Cadet::getFlightStr(Cadet::FLIGHT::TANGO), Cadet::FLIGHT::TANGO},
	{Cadet::getFlightStr(Cadet::FLIGHT::UNIFORM), Cadet::FLIGHT::UNIFORM},
	{Cadet::getFlightStr(Cadet::FLIGHT::VICTOR), Cadet::FLIGHT::VICTOR},
	{Cadet::getFlightStr(Cadet::FLIGHT::WHISKEY), Cadet::FLIGHT::WHISKEY},
	{Cadet::getFlightStr(Cadet::FLIGHT::XRAY), Cadet::FLIGHT::XRAY},
	{Cadet::getFlightStr(Cadet::FLIGHT::YANKEE), Cadet::FLIGHT::YANKEE},
	{Cadet::getFlightStr(Cadet::FLIGHT::ZULU), Cadet::FLIGHT::ZULU},
	{Cadet::getFlightStr(Cadet::FLIGHT::TRAINING), Cadet::FLIGHT::TRAINING},
	{Cadet::getFlightStr(Cadet::FLIGHT::STAFF), Cadet::FLIGHT::STAFF}
};

Cadet::Cadet(int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes) {
    this->capid = capid;
    this->grade = grade;
    this->rank = rank;
    this->firstName = firstName;
    this->lastName = lastName;
    this->flight = flight;
    this->notes = notes;
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
		default:
			return lastName+", "+firstName;
    }
}

QString Cadet::getID() const {
	return QString::number(capid);
}

void Cadet::read(const QJsonObject& json) {
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
	return QString::number(capid)+", "+getGradeStr(grade)+", "+getRankStr(rank)+", "+firstName+", "+lastName+", "+getFlightStr(flight)+", "+notes;
}
