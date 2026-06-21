#include "creature.h"
#include"random.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature() : name("") {}
Creature::Creature(string name, unsigned int hp, unsigned int mp,
                   unsigned int agi, unsigned int atk, unsigned int matk,
                   unsigned int def, unsigned int mdef, unsigned int dex,
                   unsigned int luk)
    : name(name) {
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
unsigned int Creature::getMaxHp() const {
  return status.at("maxHp").getFinalValue();
}
unsigned int Creature::getHp() const { return status.at("hp").getFinalValue(); }
unsigned int Creature::getMaxMp() const {
  return status.at("maxMp").getFinalValue();
}
unsigned int Creature::getMp() const { return status.at("mp").getFinalValue(); }
unsigned int Creature::getAgi() const {
  return status.at("agi").getFinalValue();
}
unsigned int Creature::getAtk() const {
  return status.at("atk").getFinalValue();
}
unsigned int Creature::getMatk() const {
  return status.at("matk").getFinalValue();
}
unsigned int Creature::getDef() const {
  return status.at("def").getFinalValue();
}
unsigned int Creature::getMdef() const {
  return status.at("mdef").getFinalValue();
}
unsigned int Creature::getDex() const {
  return status.at("dex").getFinalValue();
}
unsigned int Creature::getLuk() const {
  return status.at("luk").getFinalValue();
}
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

unsigned int Creature::getStatBase(const string &theStatus) const {
  if (status.count(theStatus)) {
    return status.at(theStatus).base;
  }
  return 0;
}

unsigned int Creature::getStatTotal(const string& theStatus) const{
  if(status.count(theStatus)){
    return status.at(theStatus).getFinalValue();
  }
  return 0;
}

double Creature::getAcc(const Creature &target) const {
  return (getDex() * 2 + getLuk() * 0.5 - target.getAgi())/100.0;
}

double Creature::getCri() const {
  return (getLuk() * 1.5 + getDex() * 0.5)/100.0;
}

void Creature::addBonusFlat(const string &theStatus, unsigned int theValue) {
  if (status.count(theStatus)) {
    status[theStatus].base += theValue;
  }
}

void Creature::addBonusPercent(const string &theStatus, unsigned int theValue) {
  if (status.count(theStatus)) {
    status[theStatus].base += theValue;
  }
}

void Creature::heal(unsigned int theHp) { setHp(getHp() + theHp); }

void Creature::attack(Creature &target, unsigned int rawDamage) const {
  unsigned int finalDamage = rawDamage;
  bool isCrit = Random::getChance(getCri());
  if(isCrit){
    finalDamage = static_cast<unsigned int>(finalDamage*2);
    cout << this->getName() << " 暴擊成功！\n";
  }
  unsigned int actualDamage = finalDamage - target.getDef()/2;
  if(actualDamage <= 0){
    actualDamage = 0;
  }
  cout << this->getName() << " 對 " << target.getName() << " 造成了 " << actualDamage << " 點物理傷害！\n";
  target.takeDamage(actualDamage);
}
void Creature::magicAttack(Creature& target, unsigned int rawMagicDamage) const{
  unsigned int finalDamage = rawMagicDamage;
  bool isCrit = Random::getChance(getCri());
  if(isCrit){
    finalDamage = static_cast<unsigned int>(finalDamage*2);
    cout << this->getName() << " 暴擊成功！\n";
  }
  int actualDamage = finalDamage - target.getMdef()/2;
  if(actualDamage <= 0){
    actualDamage = 0;
  }
  cout << this->getName() << " 對 " << target.getName() << " 造成了 " << actualDamage << " 點魔法傷害！\n";
  target.takeDamage(actualDamage);
}
void Creature::takeDamage(int damage) {
  if (damage >= getHp()) {
    setHp(0);
  } else {
    setHp(getHp() - damage);
  }
}

void Creature::healMp(unsigned int theMp) { setMp(getMp() + theMp); }

void Creature::loseMp(unsigned int theMp) {
  unsigned int currentMp = getMp();
  setMp((currentMp > theMp) ? currentMp - theMp : 0);
}

bool Creature::isAlive() { return getHp(); }
void Creature::showInfo() const{
  cout << getName() << endl << "|-hp: " << getHp() << endl;
}
