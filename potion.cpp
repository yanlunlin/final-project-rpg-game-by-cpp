#include "potion.h"

Potion::Potion(std::string potionName, std::string statKey, int effectValue, int amount) 
    : Item(potionName, statKey, effectValue, amount) {
}