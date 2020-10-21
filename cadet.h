#ifndef CADET_H
#define CADET_H

#include <QString>

class Cadet {
public:

    enum GRADE {
        CADET,
        SENIORMEMBER
    };

    enum RANK {
        BASIC,
        AMN,
        A1C,
        SRA,
        SSGT,
        TSGT,
        MSGT,
        SMSGT,
        CMSGT,
        LT2ND,
        LT1ST,
        CAPT,
        MAJ,
        LTCOL,
        COL
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

};

#endif // CADET_H
