/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef CADET_H
#define CADET_H

#include <QJsonObject>
#include <QString>

/**
 * @brief Holds all data related to a single CAP Cadet or Senior Member
 */
class Cadet {
public:

    enum GRADE {
		CADET = 0,
		SENIORMEMBER = 1
    };

    enum RANK {
        VISITOR,

        //Cadet ranks
        BASIC,   //Airman Basic
        AMN,     //Airman
        A1C,     //Airman 1st Class
        SRA,     //Senior Airman
        SSGT,    //Staff Sergeant
        TSGT,    //Technical Sergeant
        MSGT,    //Master Sergeant
        SMSGT,   //Senior Master Sergeant
        CMSGT,   //Chief Master Sergeant

        //Shared with SMs and Cadets
        LT2ND,   //2nd Lieutenant           10
        LT1ST,   //1st Liutenant            11
        CAPT,    //Captain                  12
        MAJ,     //Major                    13
        LTCOL,   //Lieutenant Colonel       14
        COL,     //Colonel                  15

        //SM ranks
        SM,      //Senior Member            16
        FO,      //Flight Officer           17
        TFO,     //Technical Flight Officer 18
        SFO,     //Senior Flight Officer    19
        BRIGGEN, //Brigadier General        20
        MAJGEN   //Major General            21
    };

    enum FLIGHT {
        ALPHA,
        BRAVO,
        CHARLIE,
        DELTA,
        ECHO,
        FOXTROT,
        GOLF,
        HOTEL,
        INDIA,
        JULIET,
        KILO,
        LIMA,
        MIKE,
        NOVEMBER,
        OSCAR,
        PAPA,
        QUEBEC,
        ROMEO,
        SIERRA,
        TANGO,
        UNIFORM,
        VICTOR,
        WHISKEY,
        XRAY,
        YANKEE,
        ZULU,

        TRAINING,
        STAFF,
        UNASSIGNED
    };
    
	/**
	 * @brief How a name should be formatted.
	 * LASTFIRST: Last name, First name (Hamilton, Stephen)
	 * FIRSTLAST: First name Last name (Stephen Hamilton)
	 * GRADELASTFIRST: Grade/Rank Last name, First name (C/2Lt Hamilton, Stephen)
	 * GRADEFIRSTLAST: Grade/Rank First name Last name (C/2Lt Stephen Hamilton)
	 */
    enum NAMEFORMAT {
        LASTFIRST,
        FIRSTLAST,
		GRADELASTFIRST,
		GRADEFIRSTLAST
    };

	/**
	 * @brief The identifier used in the `DataManager` that indexes this member
	 */
	QString uuid;
    int capid;
	/**
	 * @brief Cadet or Senior Member
	 */
    GRADE grade;
    RANK rank;
	QString firstName;
	QString lastName;
    FLIGHT flight;
    QString notes;

	/**
	 * @brief The Complete Setup constructor.
	 * @param uuid A generated QUuid converted to QString. This is indexed in the `DataManager`.
	 * @param capid The member's CapID.
	 * @param grade The member's grade (Cadet or Senior Member).
	 * @param rank The member's current rank.
	 * @param firstName The member's first name.
	 * @param lastName The member's last name.
	 * @param flight The flight this member is currently in.
	 */
	Cadet(QString uuid, int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes);
    Cadet();

	/**
	 * @brief Converts a RANK enum into a human readable QString. See `Cadet::getShortRankStr(RANK rank)` for a shorter QString.
	 * @param rank A RANK enum to convert to QString.
	 * @return A QString that was made from the RANK enum supplied.
	 */
	static QString getRankStr(RANK rank);
	/**
	 * @brief Converts the member's rank into a human readable QString. See `Cadet::getShortRankStr()` for a shorter QString.
	 * @return A QString that was made from the member's rank.
	 */
	QString getRankStr() const;
	/**
	 * @brief Converts a RANK enum into an abbreviated human readable QString. See `Cadet::getRankStr(RANK rank)` for a longer QString.
	 * @param rank A RANK enum to convert to an abbreviated QString.
	 * @return An abbreviated QString that was made from the RANK enum supplied.
	 */
	static QString getShortRankStr(RANK rank);
	/**
	 * @brief Converts the member's rank into an abbreviated human readable QString. See `Cadet::getRankStr()` for a longer QString.
	 * @return An abbreviated QString that was made from the member's rank.
	 */
	QString getShortRankStr() const;
	/**
	 * @brief Converts a FLIGHT enum into a human readable QString.
	 * @param flight A FLIGHT enum to convert to QString.
	 * @return A QString that was made from the FLIGHT enum supplied.
	 */
	static QString getFlightStr(FLIGHT flight);
	/**
	 * @brief Converts the member's flight into a human readable QString.
	 * @return A QString that was made from the member's flight.
	 */
	QString getFlightStr() const;
	/**
	 * @brief Converts a GRADE enum into a human readable QString. See `Cadet::getShortGradeStr(GRADE grade, bool slash = true)` for a shorter QString.
	 * @param grade A GRADE enum to convert to QString.
	 * @return A QString that was made from the GRADE enum supplied.
	 */
	static QString getGradeStr(GRADE grade);
	/**
	 * @brief Converts the member's grade into a human readable QString. See `Cadet::getShorterGradeStr(bool slash = true)` for a shorter QString.
	 * @return A QString that was made from the member's grade.
	 */
	QString getGradeStr() const;
	/**
	 * @brief Converts a GRADE enum into an abbreviated human readable QString. See `Cadet::getGradeStr(GRADE grade)` for a longer QString.
	 * @param grade A GRADE enum to convert into an abbreviated QString.
	 * @param slash Whether or not to have the slash after the grade (C/ or SM/)
	 * @return An abbreviated QString that was made from the GRADE enum supplied.
	 */
	static QString getShortGradeStr(GRADE grade, bool slash = true);
	/**
	 * @brief Converts the member's grade into an abbreviated human readable QString. See `Cadet::getGradeStr()` for a longer QString.
	 * @param slash Whether or not to have the slash after the grade (C/ or SM/).
	 * @return An abbreviated QString that was made from the member's grade.
	 */
	QString getShortGradeStr(bool slash = true) const;
	/**
	 * @brief Returns a formatted QString using the cadet's name and/or rank.
	 * @param The way the name should be formatted. See `Cadet::NAMEFORMAT` to see what the formatting options do.
	 * @return A formatted QString.
	 */
	QString getFormattedName(NAMEFORMAT format = NAMEFORMAT::LASTFIRST) const;
	/**
	 * @brief Returns the leadership phase that the cadet is currently in.
	 * @return an int that resembles the phase.
	 */
	int getPhase() const;

	/**
	 * @brief Sets all variables to values read from the QJsonObject, if they exist, supplied by the `DataManager`.
	 * @param A reference to a QJsonObject read from a file.
	 */
    void read(const QJsonObject& json);
	/**
	 * @brief Writes all variables to a QJsonObject to be written to a file later by the `DataManager`.
	 * @param A reference to a QJsonObject that is to be written to a file.
	 */
    void write(QJsonObject& json) const;

	/**
	 * @brief Debug purposes.
	 */
    QString toString();

};

#endif // CADET_H
