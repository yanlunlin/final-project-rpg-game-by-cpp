#include "monster.h"
#include "player.h"
#include <iostream>

Monster::Monster() : name(""), rewardGold(0) {}
Monster::Monster(string name, int hp, int attackPower, int rewardGold)
    : name(name), rewardGold(rewardGold) {
  proper["hp"] = hp;
  proper["atk"] = attackPower;
}

string Monster::getName() const { return name; }
unsigned int Monster::getHp() const { return proper.at("hp"); }
unsigned int Monster::getAttackPower() const { return proper.at("atk"); }
int Monster::getRewardGold() const { return rewardGold; }

void Monster::attack(Player &target) const {
  target.takeDamage(*this, getAttackPower());
}
bool Monster::takeDamage(Player &target, int damage) {
  if (damage >= getHp()) {
    target.setHp(0);
    return 0;
  } else {
    target.setHp(getHp() - damage);
    return 1;
  }
  return 1;
}

bool Monster::isAlive() { return getHp(); }
void Monster::showInfo() {
  cout << getName() << endl << "|-hp: " << getHp() << endl;
}

Slime::Slime() : Monster("Slime", 0, 0, 0) {}
Slime::Slime(string name, int hp, int attackPower, int rewardGold)
    : Monster(name + " Slime", hp, attackPower, rewardGold) {}
