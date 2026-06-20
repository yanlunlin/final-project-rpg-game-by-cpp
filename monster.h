#pragma once
#include "creature.h"
#include "effect.h"
#include "random.h"
#include "skill.h"
#include <future>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Player;

class Monster : public Creature {
protected:
  unsigned int rewardGold;
  vector<Skill> skillBook;

public:
  Monster();

  Monster(string name, // name of the monster
          vector<Skill> skillBook,
          unsigned int hp,   // health value
          unsigned int mp,   // magic value
          unsigned int agi,  // stealth
          unsigned int atk,  // attack value
          unsigned int matk, // magic attcak value
          unsigned int def,  // defence value
          unsigned int mdef, // magic defence value
          unsigned int dex,  // dexterity
          unsigned int luk,  // lucky
          int rewardGold);   // gold drops when killed

  unsigned int getRewardGold() const;
  void setRewardGold(unsigned int rewardGold);
};

class MonsterSkill : public Skill {
protected:
  enum class target { player, all };
  vector<Effect *> effect;
  vector<target> targett;

public:
  MonsterSkill();
  MonsterSkill(string theName, int theDamage);

  void use(vector<Creature *> team) const override;
};

class Slime : public Monster {
public:
  Slime();
  Slime(string name, unsigned int hp, unsigned int mp, unsigned int agi,
        unsigned int atk, unsigned int matk, unsigned int def,
        unsigned int mdef, unsigned int dex, unsigned int luk, int rewardGold);
};

class Succubus : public Monster {};
