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

void Cadet::read(const QJsonObject &json) {
    if(json.contains("capid") && json["capid"].isDouble()){
        capid = json["capid"].toInt();
    }

    if(json.contains("grade") && json["grade"].isDouble()){
        grade = GRADE(json["grade"].toInt());
    }

    if(json.contains("rank") && json["rank"].isDouble()){
        rank = RANK(json["rank"].toInt());
    }

    if(json.contains("firstName") && json["firstName"].isString()){
        firstName = json["firstName"].toString();
    }

    if(json.contains("lastName") && json["lastName"].isString()){
        lastName = json["lastName"].toString();
    }

    if(json.contains("flight") && json["flight"].isDouble()){
        flight = FLIGHT(json["flight"].toInt());
    }

    if(json.contains("notes") && json["notes"].isString()){
        notes = json["notes"].toString();
    }
}

void Cadet::write(QJsonObject &json) const {
    json["capid"] = capid;
    json["grade"] = grade;
    json["rank"] = rank;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["flight"] = flight;
    json["notes"] = notes;
}
