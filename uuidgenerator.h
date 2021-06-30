#ifndef UUIDGENERATOR_H
#define UUIDGENERATOR_H

#include <QUuid>

class UUIDGenerator
{
public:
    UUIDGenerator();

    enum IDType {
        STANDARD,
        CADET,
        ITEM,
        CARD,
        CHANGE
    };

    static QString generateUUID(IDType idType = IDType::STANDARD, QString uuid = "");

private:

    static void removeBraces(QString &uuid);

};

#endif // UUIDGENERATOR_H
