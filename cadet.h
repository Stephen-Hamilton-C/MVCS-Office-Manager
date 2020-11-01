#ifndef CADET_H
#define CADET_H

#include <QJsonObject>
#include <QString>

class Cadet {
public:

    enum GRADE {
        CADET,
        SENIORMEMBER
    };

    enum RANK {
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
        LT2ND,   //2nd Lieutenant
        LT1ST,   //1st Liutenant
        CAPT,    //Captain
        MAJ,     //Major
        LTCOL,   //Lieutenant Colonel
        COL,     //Colonel

        //SM ranks
        SM,      //Senior Member
        FO,      //Flight Officer
        TFO,     //Technical Flight Officer
        SFO,     //Senior Flight Officer
        BRIGGEN, //Brigadier General
        MAJGEN   //Major General
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
    
    int capid;
    GRADE grade;
    RANK rank;
    QString firstName;
    QString lastName;
    FLIGHT flight;
    QString notes;

    Cadet(int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes);
    Cadet();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    int getPhase();

    QString toString();

};

#endif // CADET_H
