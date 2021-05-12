/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include "cadet.h"

/**
 * @brief Contains several constant variables that are used across the entire application.
 */
namespace Constants {

	/**
	 * @brief The display name of the application
	 */
    const QString name = "Office Manager";
	/**
	 * @brief The current version of the application
	 */
    const QString version = "DEV";
	/**
	 * @brief The default name and extension that the data file is named
	 */
	const QString defaultSaveFileName = "MVCS-Manager-Data.json";

    /**
     * @brief The day of the week the squadron meets up. 1 = Monday, 7 = Sunday
     */
    const int meetingDay = 4;

	/**
	 * @brief The labels that show at the top of the cadet view
	 */
	const QStringList cadetTableHeader {"UUID", "CapID", "Grade", "Rank", "Name", "Flight", "Notes"};
	/**
	 * @brief The labels that show at the top of the insepction log view
	 */
	const QStringList cardTableHeader {"UUID", "Flight", "Cadet", "Date", "Appearance", "Garments", "Accountrements", "Footwear", "Bearing", "Overall"};
	/**
	 * @brief The labels that show at the top of the supply item view
	 */
    const QStringList itemTableHeader {"UUID", "Name", "Category", "Count", "Properties"};

	/**
	 * @brief The labels that show at the top of the properties view in the supply item editor
	 */
	const QStringList itemPropertyTableHeaders { "Name", "Value" };

	/**
	 * @brief The selections for a comboBox that lists cadet ranks
	 */
	const QMap<QString, Cadet::RANK> comboBox_CadetRanks {
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
	/**
	 * @brief The selections for a comboBox that lists senior member ranks
	 */
	const QMap<QString, Cadet::RANK> comboBox_SMRanks {
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
	/**
	 * @brief The selections for a comboBox that lists flights
	 */
	const QMap<QString, Cadet::FLIGHT> comboBox_Flight {
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

};

#endif // CONSTANTS_H
