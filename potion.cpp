#include "potion.h"

Potion::Potion(std::string potionName, std::string statKey, ValueType theType, int effectValue, unsigned int turns, int amount) 
    : Item(potionName, "Potion", Effect(potionName, statKey, theType, effectValue, turns), amount) {
}