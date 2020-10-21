#include "cadet.h"

Cadet::Cadet(int capid, GRADE grade, RANK rank, QString firstName, QString lastName, FLIGHT flight, QString notes) {
    this->capid = capid;
    this->grade = grade;
    this->rank = rank;
    this->firstName = firstName;
    this->lastName = lastName;
    this->flight = flight;
    this->notes = notes;
}


