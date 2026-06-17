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
  Monster(string name, int hp, int attackPower, int rewardGold);
  int getRewardGold() const;
};

class Slime : public Monster {
public:
  Slime();
  Slime(string name, int hp, int attackPower, int rewardGold);
};

class Succubus : public Monster {};
