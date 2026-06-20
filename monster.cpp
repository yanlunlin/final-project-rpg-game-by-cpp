#include "monster.h"
#include "creature.h"
#include "player.h"
#include <iostream>

Monster::Monster() : Creature(), rewardGold(0) {}
Monster::Monster(string name, unsigned int hp, unsigned int mp, unsigned int agi,
    unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
    unsigned int dex, unsigned int luk, int rewardGold)
    : Creature(name, hp, mp, agi, atk, matk, def, mdef, dex, luk), rewardGold(rewardGold) {}

int Monster::getRewardGold() const { return rewardGold; }

Slime::Slime() : Monster("Slime", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
Slime::Slime(string name, unsigned int hp, unsigned int mp, unsigned int agi,
    unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
    unsigned int dex, unsigned int luk, int rewardGold)
    : Monster(name + " Slime", hp, mp, agi, atk, matk, def, mdef, dex, luk, rewardGold) {}
