#include "supplyitem.h"

SupplyItem::SupplyItem(QString name, int count, int lowCountThreshold, QVariantMap properties){
    this->name = name;
    this->count = count;
    this->lowCountThreshold = lowCountThreshold;
    this->properties = properties;
}

void SupplyItem::read(const QJsonObject& json) {
    if(json.contains("item_name") && json["item_name"].isString()){
        name = json["item_name"].toString();
    }

    if(json.contains("item_count") && json["item_count"].isDouble()){
        count = json["item_count"].toInt();
    }
    
    if(json.contains("item_lowCountThreshold") && json["item_lowCountThreshold"].isDouble()){
        lowCountThreshold = json["item_lowCountThreshold"].toInt();
    }

    //It's a lot easier to work with QVariantMaps in QJson than it is with regular QMaps
    if(json.contains("item_properties") && json["item_properties"].isObject()){
        properties = json["item_properties"].toObject().toVariantMap();
    }
}

void SupplyItem::write(QJsonObject& json) const {
    json["item_name"] = name;
    json["item_count"] = count;
    json["item_lowCountThreshold"] = lowCountThreshold;
    json["item_properties"] = QJsonObject::fromVariantMap(properties);
}
