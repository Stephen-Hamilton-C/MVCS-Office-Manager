/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef INSPECTIONCARD_H
#define INSPECTIONCARD_H

#include "cadet.h"

#include <QJsonArray>

class InspectionCard {
public:
	enum RATING {
		NEEDSIMPROVEMENT = 0,
		SATISFACTORY = 1,
		EXCELLENT = 2
	};

	InspectionCard(QString uuid, QString cadetUUID, QDate date,
				   RATING appearanceScore, RATING garmentsScore, RATING accountrementsScore, RATING footwearScore, RATING bearingScore);
    InspectionCard();

	QString uuid;
	QString cadetUUID;
	int cadetPhaseAtInspect;
	Cadet::FLIGHT cadetFlightAtInspect;
    QDate date;

    RATING appearanceScore;
    RATING garmentsScore;
    RATING accountrementsScore;
    RATING footwearScore;
    RATING bearingScore;

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
