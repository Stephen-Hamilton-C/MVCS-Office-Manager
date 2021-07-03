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

#include "item.h"
#include "cadet.h"

#include <QJsonObject>

/**
 * @brief Holds all data related to a single Inspection Log Entry
 */
class InspectionCard: public Item {
public:

	void takeSnapshot() override;

	/**
	 * @brief The three possible ratings a section can have.
	 * NEEDSIMPROVEMENT: A score of 0.
	 * SATISFACTORY: A score of 1.
	 * EXCELLENT: A score of 2.
	 */
	enum RATING {
		NEEDSIMPROVEMENT = 0,
		SATISFACTORY = 1,
		EXCELLENT = 2
	};

	/**
	 * @brief The Complete Setup constructor
	 * @param uuid A generated QUuid converted to QString. This is indexed in the `DataManager`.
	 * @param cadetUUID The UUID of the cadet that received this inspection.
	 * @param date The date when this inspection was done.
	 */
	InspectionCard(QString uuid, QString cadetUUID, QDate date,
				   RATING appearanceScore, RATING garmentsScore, RATING accountrementsScore, RATING footwearScore, RATING bearingScore);
	InspectionCard();

	/**
	 * @brief The identifier of the cadet that received this inspection.
	 */
	QString cadetUUID;
	/**
	 * @brief The leadership phase this cadet was at when the inspection was issued. This affects the overall rating.
	 */
	int cadetPhaseAtInspect;
	/**
	 * @brief The flight this cadet was in when the inspection was issued. This allows for correct scoring of flights in inspections.
	 */
	Cadet::FLIGHT cadetFlightAtInspect;
	/**
	 * @brief The date when this inspection was issued.
	 */
	QDate date;

	//These are self-explanatory, no documentation needed.
	RATING appearanceScore;
	RATING garmentsScore;
	RATING accountrementsScore;
	RATING footwearScore;
	RATING bearingScore;

	/**
	 * @brief Returns the numerical total points the cadet got on this inspection. Leadership phase does not affect the result.
	 * @return The total amount of points the cadet got on the inspection.
	 */
	int getTotalPoints() const;
	/**
	 * @brief Returns the overall rating the cadet got on this inspection. Leadership phase affects the result.
	 * @return The overall rating the cadet got on the inspection.
	 */
	RATING getOverallRating() const;
	/**
	 * @brief Converts a 0, 1, or 2 into a QString corresponding to the number. See RATING for more information.
	 * @param score The score to convert into a QString
	 * @return A QString containing the text translation of a simple score. See RATING for more information.
	 */
	QString getRatingString(int score) const;
	/**
	 * @brief Converts a RATING enum into a QString.
	 * @param rating The RATING enum to convert into a QString
	 * @return A QString containing the text translation of a RATING enum. See RATING for more information.
	 */
	QString getRatingString(RATING rating) const;
	/**
	 * @brief Gets a pointer to the cadet that received this inspection.
	 * @return A Cadet pointer found in the `DataManager` from the `InspectionCard::cadetUUID`.
	 */
	Cadet* getCadet() const;


	/**
	 * @brief see Serializable::read
	 */
	void read(const QJsonObject& json) override;
	/**
	 * @brief see Serializable::write
	 */
	void write(QJsonObject& json) const override;

	/**
	 * @brief Debug purposes.
	 */
	QString toString();

private:

	static int _day;

};

#endif // INSPECTIONCARD_H
