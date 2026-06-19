#pragma once
#include "creature.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class Player;

class Monster : public Creature {
protected:
  unsigned int rewardGold;

public:
  Monster();
  Monster(string name, unsigned int hp, unsigned int mp, unsigned int agi,
    unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
    unsigned int dex, unsigned int luk, int rewardGold);
  int getRewardGold() const;
};

class Slime : public Monster {
public:
  Slime();
  Slime(string name, unsigned int hp, unsigned int mp, unsigned int agi,
    unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
    unsigned int dex, unsigned int luk, int rewardGold);
};

class Succubus : public Monster {};
