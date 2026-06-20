#include "equipment.h"

Equipment::Equipment(std::string equipName, int defValue, int amount) 
    : Item(equipName, "def", defValue, amount) {
}