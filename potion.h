#ifndef POTION_H
#define POTION_H

#include "item.h"
#include <string>

class Potion : public Item {
public:
    // statKey -> "hp", "mp", "agi", "atk"
    Potion(std::string potionName, std::string statKey, int effectValue, int amount);
};

#endif