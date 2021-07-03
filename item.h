#ifndef ITEM_H
#define ITEM_H

#endif // ITEM_H

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
