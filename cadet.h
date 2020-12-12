#ifndef CADET_H
#define CADET_H

#include <QJsonObject>
#include <QString>

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
    
    enum NAMEFORMAT {
        LASTFIRST,
        FIRSTLAST,
    };

	QString uuid;
    int capid;
    GRADE grade;
    RANK rank;
	QString firstName;
	QString lastName;
    FLIGHT flight;
    QString notes;

	Cadet(QString uuid, int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes);
    Cadet();

	static QString getRankStr(RANK rank);
	QString getRankStr() const;
	static QString getShortRankStr(RANK rank);
	QString getShortRankStr() const;
	static QString getFlightStr(FLIGHT flight);
	QString getFlightStr() const;
	static QString getGradeStr(GRADE grade);
	QString getGradeStr() const;
	static QString getShortGradeStr(GRADE grade, bool slash = true);
	QString getShortGradeStr(bool slash = true) const;
	QString getFormattedName(NAMEFORMAT format = NAMEFORMAT::LASTFIRST) const;
	QString getID() const;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

	int getPhase() const;

    QString toString();

};

#endif // CADET_H
