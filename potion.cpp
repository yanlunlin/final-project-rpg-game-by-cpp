#include "potion.h"

Potion::Potion(std::string potionName, std::string statKey, int effectValue, int amount) 
    : item(potionName, statKey, effectValue, amount) {
}