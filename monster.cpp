#include "monster.h"
#include "player.h"
#include <iostream>

Monster::Monster() : name(""), hp(0), attackPower(0), rewardGold(0) {}
Monster::Monster(string name, int hp, int attackPower, int rewardGold)
    : name(name), hp(hp), attackPower(attackPower), rewardGold(rewardGold) {}

string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getAttackPower() const { return attackPower; }
int Monster::getRewardGold() const { return rewardGold; }

void Monster::attack(Player &target) const {
  target.takeDamage(&target, getAttackPower());
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
