#include "changesmanager.h"
#include "change.h"

#include <QJsonArray>

ChangesManager::ChangesManager()
{

}

Change* ChangesManager::createChange(QString objectUUID, QString uuid, QString property, QVariant value, QDate date)
{
    _changes.append(Change(objectUUID, uuid, property, value, date));
    Change* change = &_changes.last();
    index(change);
    return change;
}

Change* ChangesManager::fromObjectUUID(QString objectUUID, QString property)
{
    return _objectUUIDMap[objectUUID][property];
}

QList<Change*> ChangesManager::fromDate(QDate date)
{
    return _dateMap[date];
}

void ChangesManager::read(const QJsonObject &json)
{
    if(json.contains("changes") && json["changes"].isArray()){
        const QJsonArray jChanges = json["changes"].toArray();
        for(int i = 0; i < jChanges.count(); i++){
            Change change;
            change.read(json["changes"][i].toObject());
            _changes.append(change);
        }
    }

    reindex();
}

void ChangesManager::write(QJsonObject &json)
{
    QJsonArray jChanges;
    for(int i = 0; i < _changes.count(); i++){
        QJsonObject changeJObj;
        _changes[i].write(changeJObj);
        jChanges.append(changeJObj);
    }

    json["changes"] = jChanges;
}

void ChangesManager::reindex()
{
    _dateMap.clear();
    _objectUUIDMap.clear();

    for(int i = 0; i < _changes.count(); i++){
        Change* change = &_changes[i];
        index(change);
    }
}

void ChangesManager::index(Change *change)
{
    if(_dateMap.contains(change->date)){
        _dateMap[change->date].append(change);
    } else {
        _dateMap.insert(change->date, QList<Change*>() << change);
    }

    if(_objectUUIDMap.contains(change->objectUUID)){
        _objectUUIDMap[change->objectUUID].insert(change->property, change);
    } else {
        _objectUUIDMap.insert(change->objectUUID, QMap<QString, Change*>{{change->property, change}});
    }
}
