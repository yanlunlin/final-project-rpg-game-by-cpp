#include "weapon.h"

Weapon::Weapon(std::string weaponName, int atkValue, int amount) 
    : item(weaponName, "atk", atkValue, amount) {
}