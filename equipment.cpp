#include "equipment.h"

Equipment::Equipment(std::string equipName, int defValue, ValueType theType, int amount)
    : Item(equipName, "Equipment", Effect(equipName, "def", theType, defValue, 0), amount) {}