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
class MonsterSkill;

class Monster : public Creature {
protected:
  unsigned int rewardGold;
  vector<MonsterSkill *> skillBook;

public:
  Monster();
  Monster(string name, vector<MonsterSkill *> skillBook, unsigned int hp,
          unsigned int agi, unsigned int atk, unsigned int matk,
          unsigned int def, unsigned int mdef, int rewardGold);

  unsigned int getRewardGold() const;
  void setRewardGold(unsigned int rewardGold);

  void action(vector<Creature *> team, vector<Creature *> monster) override;
};

class MonsterSkill : public Skill {
public:
  enum class target { player, all };

private:
  vector<Effect *> effects;
  target skillTarget;

public:
  MonsterSkill();
  MonsterSkill(string theName, target tgt, int theDamageCross,
               vector<Effect *> eff);

  void addEffect(Effect *eff, target tgt);
  void use(vector<Creature *> team, Creature *user) const;
  MonsterSkill &attach(Effect *eff, target tgt);
};
