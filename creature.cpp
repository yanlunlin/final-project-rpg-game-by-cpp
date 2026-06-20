#include "creature.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature() : name("") {}
Creature::Creature(string name, unsigned int hp, unsigned int mp, unsigned int agi,
  unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
  unsigned int dex, unsigned int luk) : name(name) {
  status["maxHp"].base = hp;
  status["hp"].base = hp;
  status["maxMp"].base = mp;
  status["mp"].base = mp;
  status["agi"].base = agi;
  status["atk"].base = atk;
  status["matk"].base = matk;
  status["def"].base = def;
  status["mdef"].base = mdef;
  status["dex"].base = dex;
  status["luk"].base = luk;
}

string Creature::getName() const { return name; }
unsigned int Creature::getMaxHp() const { return status.at("maxHp").getFinalValue(); }
unsigned int Creature::getHp() const { return status.at("hp").getFinalValue(); }
unsigned int Creature::getMaxMp() const { return status.at("maxMp").getFinalValue(); }
unsigned int Creature::getMp() const { return status.at("mp").getFinalValue(); }
unsigned int Creature::getAgi() const { return status.at("agi").getFinalValue(); }
unsigned int Creature::getAtk() const { return status.at("atk").getFinalValue(); }
unsigned int Creature::getMatk() const { return status.at("matk").getFinalValue(); }
unsigned int Creature::getDef() const { return status.at("def").getFinalValue(); }
unsigned int Creature::getMdef() const {return status.at("mdef").getFinalValue(); }
unsigned int Creature::getDex() const { return status.at("dex").getFinalValue(); }
unsigned int Creature::getLuk() const { return status.at("luk").getFinalValue(); }
void Creature::setName(string name) { this->name = name; }
void Creature::setMaxHp(unsigned int maxHp) { status["maxHp"].base = maxHp; }
void Creature::setHp(unsigned int hp) {
  unsigned int currentMaxHp = getMaxHp();
  status["hp"].base = (hp > currentMaxHp) ? currentMaxHp : hp;
}
void Creature::setMaxMp(unsigned int maxMp) { status["maxMp"].base = maxMp; }
void Creature::setMp(unsigned int mp) {
  unsigned int currentMaxMp = getMaxMp();
  status["mp"].base = (mp > currentMaxMp) ? currentMaxMp : mp;
}
void Creature::setAgi(unsigned int agi) { status["agi"].base = agi; }
void Creature::setAtk(unsigned int atk) { status["atk"].base = atk; }
void Creature::setMatk(unsigned int matk) { status["matk"].base = matk; }
void Creature::setDef(unsigned int def) { status["def"].base = def; }
void Creature::setMdef(unsigned int mdef) { status["mdef"].base = mdef; }
void Creature::setDex(unsigned int dex) { status["dex"].base = dex; }
void Creature::setLuk(unsigned int luk) { status["luk"].base = luk; }

unsigned int Creature::getAcc(const Creature& target) const{
  return getDex()*2 + getLuk()*0.5 - target.getAgi();
}

unsigned int Creature::getCri() const{
  return getLuk()*1.5 + getDex()*0.5;
}

void Creature::heal(unsigned int theHp){
  setHp(getHp() + theHp);
}

void Creature::attack(Creature &target) const {
  target.takeDamage(getAtk());
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
