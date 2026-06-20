#include "weapon.h"

Weapon::Weapon(std::string weaponName, int atkValue, int amount) 
    : Item(weaponName, "Weapon", Effect(weaponName, "atk", ValueType::Flat, atkValue, 0), amount) {
}