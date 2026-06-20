#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "effect.h"
#include "inventory.h"
#include "item.h"
#include "skill.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Monster;

class Player : public Creature {
private:
  /*map<string, unsigned int> status{
      {"hp", 0}, {"mp", 0}, {"str", 0}, {"vit", 0}, {"agi", 0}, {"dex", 0},
  {"int", 0}
  };*/

  /*map<string, unsigned int> status{
      {"hp", 0}, {"mp", 0},
      {"agi", 0}, //agility 敏捷
      {"atk", 0}, {"matk", 0},
      {"def", 0}, {"mdef", 0},
      {"dex", 0}, //dexterity 影響暴擊率及命中率, 影響命中率較多
      {"luk", 0}, //luck 影響暴擊率及命中率, 影響暴擊率較多
  };*/

  Inventory backpack;
  vector<Effect> activeEffect;
  vector<Skill> skillBook;

public:
  inline static unsigned int wallet = 0;

  Player();
  Player(string theName, unsigned int theHp, unsigned int theMp,
         unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
         unsigned int theDef, unsigned int theMdef, unsigned int theDex,
         unsigned int theLuk);

  const Inventory &getBackpack() const;
  const vector<Item> &getItemList() const;

  /*void attack(Monster& target);
  void takeDamage(const Monster& attacker, int damage);*/
  void useItem(size_t index);
};

class Swordman : public Player {
public:
  Swordman();
  Swordman(string theName);
  Swordman(string theName, unsigned int theHp, unsigned int theMp,
           unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
           unsigned int theDef, unsigned int theMdef, unsigned int theDex,
           unsigned int theLuk);
};

class SwordMaster : public Swordman {
public:
  SwordMaster();
  SwordMaster(string theName);
  SwordMaster(string theName, unsigned int theHp, unsigned int theMp,
              unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
              unsigned int theDef, unsigned int theMdef, unsigned int theDex,
              unsigned int theLuk);
};

class Warrior : public Player {
public:
  Warrior();
  Warrior(string theName);
  Warrior(string theName, unsigned int theHp, unsigned int theMp,
          unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
          unsigned int theDef, unsigned int theMdef, unsigned int theDex,
          unsigned int theLuk);
};

class Crusader : public Warrior {
public:
  Crusader();
  Crusader(string theName);
  Crusader(string theName, unsigned int theHp, unsigned int theMp,
           unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
           unsigned int theDef, unsigned int theMdef, unsigned int theDex,
           unsigned int theLuk);
};

class Wizard : public Player {
public:
  Wizard();
  Wizard(string theName);
  Wizard(string theName, unsigned int theHp, unsigned int theMp,
         unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
         unsigned int theDef, unsigned int theMdef, unsigned int theDex,
         unsigned int theLuk);
};

class ArchWizard : public Wizard {
public:
  ArchWizard();
  ArchWizard(string theName);
  ArchWizard(string theName, unsigned int theHp, unsigned int theMp,
             unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
             unsigned int theDef, unsigned int theMdef, unsigned int theDex,
             unsigned int theLuk);
};

class Priest : public Player {
public:
  Priest();
  Priest(string theName);
  Priest(string theName, unsigned int theHp, unsigned int theMp,
         unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
         unsigned int theDef, unsigned int theMdef, unsigned int theDex,
         unsigned int theLuk);
};

class ArchPriest : public Priest {
public:
  ArchPriest();
  ArchPriest(string theName);
  ArchPriest(string theName, unsigned int theHp, unsigned int theMp,
             unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
             unsigned int theDef, unsigned int theMdef, unsigned int theDex,
             unsigned int theLuk);
};

class Archer : public Player {
public:
  Archer();
  Archer(string theName);
  Archer(string theName, unsigned int theHp, unsigned int theMp,
         unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
         unsigned int theDef, unsigned int theMdef, unsigned int theDex,
         unsigned int theLuk);
};

class Thief : public Player {
public:
  Thief();
  Thief(string theName);
  Thief(string theName, unsigned int theHp, unsigned int theMp,
        unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
        unsigned int theDef, unsigned int theMdef, unsigned int theDex,
        unsigned int theLuk);
};

class Assassin : public Thief {
public:
  Assassin();
  Assassin(string theName);
  Assassin(string theName, unsigned int theHp, unsigned int theMp,
           unsigned int theAgi, unsigned int theAtk, unsigned int theMatk,
           unsigned int theDef, unsigned int theMdef, unsigned int theDex,
           unsigned int theLuk);
};

#endif
