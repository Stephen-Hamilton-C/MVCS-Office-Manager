#include "inspectioncard.h"

InspectionCard::InspectionCard() {
    qDebug() << "Creating empty Inspection Card";
}

int InspectionCard::getTotalPoints(){
    return appearanceScore + garmentsScore + accountrementsScore + footwearScore + bearingScore;
}

InspectionCard::RATING InspectionCard::getOverallRating(){
    int overallPoints = getTotalPoints();
    if(cadet.getPhase() == 1){
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

void InspectionCard::read(const QJsonObject& json){
    if(json.contains("card_cadetID") && json["card_cadetID"].isDouble()){
        cadetID = json["card_cadetID"].toInt();
    }

    if(json.contains("card_date") && json["card_date"].isArray()){
        //Year, Month, Day
        QJsonArray dateArray = json["card_date"].toArray();
        date = QDate(dateArray[0].toInt(), dateArray[1].toInt(), dateArray[2].toInt());
    }

    if(json.contains("card_appearanceScore") && json["card_appearanceScore"].isDouble()){
       appearanceScore = RATING(json["card_appearanceScore"].toInt());
    }

    if(json.contains("card_garmentsScore") && json["card_garmentsScore"].isDouble()){
        garmentsScore = RATING(json["card_garmentsScore"].toInt());
    }

    if(json.contains("card_accountrementsScore") && json["card_accountrementsScore"].isDouble()){
        accountrementsScore = RATING(json["card_accountrementsScore"].toInt());
    }

    if(json.contains("card_footwearScore") && json["card_footwearScore"].isDouble()){
        footwearScore = RATING(json["card_footwearScore"].toInt());
    }

    if(json.contains("card_bearingScore") && json["card_bearingScore"].isDouble()){
        bearingScore = RATING(json["card_bearingScore"].toInt());
    }

    if(json.contains("card_notes") && json["card_notes"].isString()){
        notes = json["card_notes"].toString();
    }
}

void InspectionCard::write(QJsonObject &json) const {
    json["card_cadetID"] = cadetID;

    QJsonArray dateArray;
    dateArray.append(date.year());
    dateArray.append(date.month());
    dateArray.append(date.day());
    json["card_date"] = dateArray;

    json["card_appearanceScore"] = appearanceScore;
    json["card_garmentsScore"] = garmentsScore;
    json["card_accountrementsScore"] = accountrementsScore;
    json["card_footwearScore"] = footwearScore;
    json["card_bearingScore"] = bearingScore;
    json["card_notes"] = notes;

}

QString InspectionCard::toString(){
    return QString(appearanceScore)+", "+QString(garmentsScore)+", "+QString(accountrementsScore)
            +", "+QString(footwearScore)+", "+QString(bearingScore)
            +", "+QString(getTotalPoints())+", "+QString(getOverallRating());
}
