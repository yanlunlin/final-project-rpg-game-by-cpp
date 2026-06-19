#pragma once
#include <map>
#include <string>
using namespace std;

class Creature {
protected:
  string name;
  map<string, unsigned int> status = {
    {"hp", 0}, {"mp", 0},
    {"agi", 0}, //agility 敏捷
    {"atk", 0}, {"matk", 0},
    {"def", 0}, {"mdef", 0},
    {"dex", 0}, //dexterity 影響暴擊率及命中率, 影響命中率較多
    {"luk", 0}, //luck 影響暴擊率及命中率, 影響暴擊率較多
  };

public:
  Creature();
  Creature(string name, unsigned int hp, unsigned int mp, unsigned int agi,
    unsigned int atk, unsigned int matk, unsigned int def, unsigned int mdef,
    unsigned int dex, unsigned int luk);
  string getName() const;
  unsigned int getHp() const;
  unsigned int getMp() const;
  unsigned int getAgi() const;
  unsigned int getAtk() const;
  unsigned int getMatk() const;
  unsigned int getDef() const;
  unsigned int getMdef() const;
  unsigned int getDex() const;
  unsigned int getLuk() const;
  void setName(string name);
  void setHp(unsigned int hp);
  void setMp(unsigned int mp);
  void setAgi(unsigned int agi);
  void setAtk(unsigned int atk);
  void setMatk(unsigned int matk);
  void setDef(unsigned int def);
  void setMdef(unsigned int mdef);
  void setDex(unsigned int dex);
  void setLuk(unsigned int luk);

  virtual void attack(Creature &target) const;
  virtual void takeDamage(int damage);
  bool isAlive();
  virtual void showInfo();
};
