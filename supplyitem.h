/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef SUPPLYITEM_H
#define SUPPLYITEM_H

#include "item.h"

#include <QJsonObject>

class SupplyItem: public Item {
public:

    void takeSnapshot() override;

    SupplyItem();
    SupplyItem(QString uuid, QString name, QString category, int count, int lowCountThreshold = 0, QVariantMap properties = QVariantMap());

    QString name;
    QString category = "Miscellaneous";
    int count;
    int lowCountThreshold;
    QVariantMap properties;

    /**
     * @brief see Serializable::read
     */
    void read(const QJsonObject& json) override;
    /**
     * @brief see Serializable::write
     */
    void write(QJsonObject& json) const override;

	QString toString() const;

private:

    static int _day;

};

#endif // SUPPLYITEM_H
