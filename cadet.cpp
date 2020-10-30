#include "cadet.h"

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

QString Cadet::toString() {
    return QString(capid)+", "+grade+", "+rank+", "+firstName+", "+lastName+", "+flight+", "+notes;
}
