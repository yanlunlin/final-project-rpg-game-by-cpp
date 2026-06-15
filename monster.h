#pragma once

#include <map>
#include <string>
#include <vector>
using namespace std;

class Player;

class Monster {
protected:
  string name;
  unsigned int rewardGold;
  map<string, unsigned int> proper = {
      {"speed", 0}, {"atk", 0}, {"hp", 0}, {"lucky", 0}, {"mp", 0}};

public:
  Monster();
  Monster(string name, int hp, int attackPower, int rewardGold);
  string getName() const;
  unsigned int getHp() const;
  unsigned int getAttackPower() const;
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
