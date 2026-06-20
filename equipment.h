#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "item.h"
#include <string>

class Equipment : public Item {
public:
    Equipment(std::string equipName, int defValue, int amount);
};

#endif