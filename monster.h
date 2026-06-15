#pragma once

#include "player.h"
#include <string>
using namespace std;

class Monster {
protected:
  string name;
  unsigned int hp, attackPower, rewardGold;

public:
  Monster();
  Monster(string name, int hp, int attackPower, int rewardGold);
  string getName() const;
  int getHp() const;
  int getAttackPower() const;
  int getRewardGold() const;

  virtual void attack(Player &target) const;
  virtual bool takeDamage(Player &target, int damage);
  bool isAlive();
  virtual void showInfo();
};

class Slime : public Monster {
public:
  Slime();
  Slime(string name, int hp, int attackPower, int rewardGold);
};

class Succubus : public Monster {};
