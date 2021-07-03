#ifndef ITEM_H
#define ITEM_H

#endif // ITEM_H

#include <QString>

class Item {
public:

    virtual void changeMade() = 0;

    /**
     * @brief The identifier used in the `DataManager` that indexes this member
     */
    QString uuid;
};
