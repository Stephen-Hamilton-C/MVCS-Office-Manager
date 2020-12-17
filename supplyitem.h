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

#include <QJsonObject>

class SupplyItem {
public:

    SupplyItem();
	SupplyItem(QString uuid, QString name, int count, int lowCountThreshold = 0, QVariantMap properties = QVariantMap());

	QString uuid;
    QString name;
    int count;
    int lowCountThreshold;
    QVariantMap properties;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

	QString toString() const;

};

#endif // SUPPLYITEM_H
