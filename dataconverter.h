/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QJsonObject>

class DataConverter
{
public:
    DataConverter();

    static void convert(QJsonObject &json);
};

#endif // DATACONVERTER_H
