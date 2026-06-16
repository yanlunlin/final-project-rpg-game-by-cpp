#include "creature.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature() : name("") {}
Creature::Creature(string name, int hp, int attackPower) : name(name) {
  proper["hp"] = hp;
  proper["atk"] = attackPower;
}

string Creature::getName() const { return name; }
unsigned int Creature::getHp() const { return proper.at("hp"); }
unsigned int Creature::getAttackPower() const { return proper.at("atk"); }
void Creature::setName(string name) { this->name = name; }
void Creature::setHp(unsigned int hp) { proper["hp"] = hp; }
void Creature::setAttackPower(unsigned int attackPower) {
  proper["atk"] = attackPower;
}

void Creature::attack(Creature &target) const {
  target.takeDamage(getAttackPower());
}
void Creature::takeDamage(int damage) {
  if (damage >= getHp()) {
    setHp(0);
  } else {
    setHp(getHp() - damage);
  }
}
bool Creature::isAlive() { return getHp(); }
void Creature::showInfo() {
  cout << getName() << endl << "|-hp: " << getHp() << endl;
}
