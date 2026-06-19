#include "creature.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature() : name("") {}
Creature::Creature(string name, unsigned int hp, unsigned int mp, unsigned int agi,
  unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
  unsigned int dex, unsigned int luk) : name(name) {
  status["hp"] = hp;
  status["mp"] = mp;
  status["agi"] = agi;
  status["atk"] = atk;
  status["matk"] = matk;
  status["def"] = def;
  status["mdef"] = mdef;
  status["dex"] = dex;
  status["luk"] = luk;
}

string Creature::getName() const { return name; }
unsigned int Creature::getHp() const { return status.at("hp"); }
unsigned int Creature::getMp() const { return status.at("mp"); }
unsigned int Creature::getAgi() const { return status.at("agi"); }
unsigned int Creature::getAtk() const { return status.at("atk"); }
unsigned int Creature::getMatk() const { return status.at("matk"); }
unsigned int Creature::getDef() const { return status.at("def"); }
unsigned int Creature::getMdef() const {return status.at("mdef"); }
unsigned int Creature::getDex() const { return status.at("dex"); }
unsigned int Creature::getLuk() const { return status.at("luk"); }
void Creature::setName(string name) { this->name = name; }
void Creature::setHp(unsigned int hp) { status["hp"] = hp; }
void Creature::setMp(unsigned int mp) { status["mp"] = mp; }
void Creature::setAgi(unsigned int agi) { status["agi"] = agi; }
void Creature::setAtk(unsigned int atk) { status["atk"] = atk; }
void Creature::setMatk(unsigned int matk) { status["matk"] = matk; }
void Creature::setDef(unsigned int def) { status["def"] = def; }
void Creature::setMdef(unsigned int mdef) { status["mdef"] = mdef; }
void Creature::setDex(unsigned int dex) { status["dex"] = dex; }
void Creature::setLuk(unsigned int luk) { status["luk"] = luk; }

unsigned int Creature::getAcc(const Creature& target) const{
  return getDex()*2 + getLuk()*0.5 - target.getAgi();
}

unsigned int Creature::getCri() const{
  return getLuk()*1.5 + getDex()*0.5;
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
