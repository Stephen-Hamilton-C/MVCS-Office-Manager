/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef ITEM_H
#define ITEM_H

#include "serializable.h"

#include <QString>

class Item: public Serializable {
public:

	virtual void takeSnapshot() = 0;

	/**
	 * @brief The identifier used in the `DataManager` that indexes this member
	 */
	QString uuid;
};

#endif // ITEM_H
