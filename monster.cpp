#include "monster.h"
#include "creature.h"
#include "player.h"
#include "skill.h"
#include <iostream>
#include <vector>

Monster::Monster() : Creature(), rewardGold(0) {}
Monster::Monster(string name, vector<Skill> skillBook, unsigned int hp,
                 unsigned int mp, unsigned int agi, unsigned int atk,
                 unsigned int matk, unsigned int def, unsigned int mdef,
                 unsigned int dex, unsigned int luk, int rewardGold)
    : Creature(name, hp, mp, agi, atk, matk, def, mdef, dex, luk),
      rewardGold(rewardGold) {}

unsigned int Monster::getRewardGold() const { return rewardGold; }
void Monster::setRewardGold(unsigned int rewardGold) {
  this->rewardGold = rewardGold;
}

MonsterSkill::MonsterSkill() : Skill() {}
MonsterSkill::MonsterSkill(string theName, int theDamage)
    : Skill(theName, theDamage, 0) {}
void MonsterSkill::use(vector<Creature *> team) const {
  for (int i = 0; i < effect.size(); i++) {
    if (targett[i] == target::all) {
      for (auto j : team) {
        effect[i]->execute(*j);
      }
    } else {
      effect[i]->execute(*team[Random::getInt(0, team.size() - 1)]);
    }
  }
}

Slime::Slime()
    : Monster("Slime",
              {
                  Skill("撞擊", 30, 0),
                  Skill(),
                  Skill(),
                  Skill(),
              },
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
Slime::Slime(string name, unsigned int hp, unsigned int mp, unsigned int agi,
             unsigned int atk, unsigned int matk, unsigned int def,
             unsigned int mdef, unsigned int dex, unsigned int luk,
             int rewardGold)
    : Monster(name + " Slime", {Skill("撞擊", 30, 0), Skill(), Skill(), Skill()},
              hp, mp, agi, atk, matk, def, mdef, dex, luk,
              rewardGold) {}
