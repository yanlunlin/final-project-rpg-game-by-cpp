#pragma once
#include <map>
#include <string>
using namespace std;

class Creature {
protected:
  string name;
  map<string, unsigned int> proper = {
      {"speed", 0}, {"atk", 0}, {"hp", 0}, {"lucky", 0}, {"mp", 0}};

public:
  Creature();
  Creature(string name, int hp, int attackPower);
  string getName() const;
  unsigned int getHp() const;
  unsigned int getAttackPower() const;
  void setName(string name);
  void setHp(unsigned int hp);
  void setAttackPower(unsigned int attackPower);

  virtual void attack(Creature &target) const;
  virtual void takeDamage(int damage);
  bool isAlive();
  virtual void showInfo();
};
