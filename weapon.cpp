#include "weapon.h"

Weapon::Weapon(std::string weaponName, int atkValue, int amount) 
    : Item(weaponName, "atk", atkValue, amount) {
}