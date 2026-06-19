#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"
#include <string>

class Weapon : public Item {
public:
    Weapon(std::string weaponName, int atkValue, int amount);
};

#endif