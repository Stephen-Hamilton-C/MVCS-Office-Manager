#ifndef INSPECTIONCARD_H
#define INSPECTIONCARD_H

#include "cadet.h"

#include <QJsonArray>

class InspectionCard {
public:
    InspectionCard();

    enum RATING {
        NEEDSIMPROVEMENT = 0,
        SATISFACTORY = 1,
        EXCELLENT = 2
    };

	QString uuid;
	QString cadetUUID;
    QDate date;

    RATING appearanceScore;
    RATING garmentsScore;
    RATING accountrementsScore;
    RATING footwearScore;
    RATING bearingScore;

    QString notes;

    int getTotalPoints();
    RATING getOverallRating();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    QString toString();

};

#endif // INSPECTIONCARD_H
