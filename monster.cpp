#include "monster.h"
#include "creature.h"
#include "player.h"
#include <iostream>

Monster::Monster() : Creature(), rewardGold(0) {}
Monster::Monster(string name, int hp, int attackPower, int rewardGold)
    : Creature(name, hp, attackPower), rewardGold(rewardGold) {}

int Monster::getRewardGold() const { return rewardGold; }

Slime::Slime() : Monster("Slime", 0, 0, 0) {}
Slime::Slime(string name, int hp, int attackPower, int rewardGold)
    : Monster(name + " Slime", hp, attackPower, rewardGold) {}
