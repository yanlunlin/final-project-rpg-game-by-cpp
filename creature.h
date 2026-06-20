#pragma once
#include "skill.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Stat {
  unsigned int base; // 基礎值
  int bonusFlat;     // 固定值加成
  int bonusPercent;  // 百分比加成

  unsigned int getFinalValue() const {
    int rawFinal = static_cast<int>(base) + bonusFlat;
    if (rawFinal < 0) {
      rawFinal = 0;
    }

    double multiplier = 1.0 + (bonusPercent / 100.0);
    return static_cast<unsigned int>(rawFinal * multiplier);
  }
};

class Creature {
protected:
  string name;
  map<string, Stat> status = {
      {"maxHp", {0, 0, 0}},
      {"hp", {0, 0, 0}},
      {"maxMp", {0, 0, 0}},
      {"mp", {0, 0, 0}},
      {"agi", {0, 0, 0}}, // agility 敏捷
      {"atk", {0, 0, 0}},
      {"matk", {0, 0, 0}},
      {"def", {0, 0, 0}},
      {"mdef", {0, 0, 0}},
      {"dex", {0, 0, 0}}, // dexterity 影響暴擊率及命中率,
                          // 影響命中率較多
      {"luk", {0, 0, 0}}, // luck 影響暴擊率及命中率, 影響暴擊率較多
  };

public:
  Creature();
  Creature(string name, unsigned int hp, unsigned int mp, unsigned int agi,
           unsigned int atk, unsigned int matk, unsigned int def,
           unsigned int mdef, unsigned int dex, unsigned int luk);
  string getName() const;
  unsigned int getMaxHp() const;
  unsigned int getHp() const;
  unsigned int getMaxMp() const;
  unsigned int getMp() const;
  unsigned int getAgi() const;
  unsigned int getAtk() const;
  unsigned int getMatk() const;
  unsigned int getDef() const;
  unsigned int getMdef() const;
  unsigned int getDex() const;
  unsigned int getLuk() const;
  void setName(string name);
  void setMaxHp(unsigned int maxHp);
  void setHp(unsigned int hp);
  void setMaxMp(unsigned int maxMp);
  void setMp(unsigned int mp);
  void setAgi(unsigned int agi);
  void setAtk(unsigned int atk);
  void setMatk(unsigned int matk);
  void setDef(unsigned int def);
  void setMdef(unsigned int mdef);
  void setDex(unsigned int dex);
  void setLuk(unsigned int luk);

  unsigned int getStatBase(const string &theStatus) const;

  unsigned int getAcc(const Creature &target) const; // Accuracy 命中率
  unsigned int getCri() const;                       // Critical 暴擊率

  void addBonusFlat(const string &theStatus, unsigned int theValue);
  void addBonusPercent(const string &theStatus, unsigned int theValue);

  virtual void action(vector<Creature *> team, vector<Creature *> monster) {};

  virtual void heal(unsigned int theHp);
  virtual void attack(Creature &target) const;
  virtual void takeDamage(int damage);
  virtual void healMp(unsigned int theMp);
  virtual void loseMp(unsigned int theMp);
  bool isAlive();
  virtual void showInfo();
};
