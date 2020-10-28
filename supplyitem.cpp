#include "supplyitem.h"

SupplyItem::SupplyItem(QString name, int count, int lowCountThreshold = 0, std::map<QString, QString> properties = NULL){
    this->name = name;
    this->count = count;
    this->lowCountThreshold = lowCountThreshold;
    this->properties = properties;
}

void SupplyItem::read(const QJsonObject& json) {
    if(json.contians("item_name") && json["item_name"].isString()){
        name = json["item_name"].toString();
    }

    if(json.contians("item_count") && json["item_count"].isDouble()){
        count = json["item_count"].toInt();
    }
    
    if(json.contians("item_lowCountThreshold") && json["item_lowCountThreshold"].isDouble()){
        lowCountThreshold = json["item_lowCountThreshold"].toInt();
    }

    //TODO: Look into if QJson can serialize maps. If not, may need to make my own.
    if(json.contians("item_properties") && json["item_properties"].isString()){
        properties = json["item_properties"].toString();
    }

}

void SupplyItem::write(QJsonObject& json) const {
    json["item_name"] = name;
    json["item_count"] = count;
    json["item_lowCountThreshold"] = lowCountThreshold;
    json["item_properties"] = properties;
}