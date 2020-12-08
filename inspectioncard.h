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

	static QStringList tableHeader;

	QString uuid;
	QString cadetUUID;
	int cadetPhaseAtInspect;
    QDate date;

    RATING appearanceScore;
    RATING garmentsScore;
    RATING accountrementsScore;
    RATING footwearScore;
    RATING bearingScore;

    QString notes;

	int getTotalPoints() const;
	RATING getOverallRating() const;
	QString getRatingString(int score) const;
	QString getRatingString(RATING rating) const;
	Cadet* getCadet() const;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    QString toString();

};

#endif // INSPECTIONCARD_H
