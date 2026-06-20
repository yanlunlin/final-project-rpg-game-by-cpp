#include "monster.h"
#include "creature.h"
#include "skill.h"
#include <iostream>
#include <vector>

Monster::Monster() : Creature(), rewardGold(0) {}
Monster::Monster(string name, vector<MonsterSkill *> skillBook, unsigned int hp,
                 unsigned int agi, unsigned int atk, unsigned int matk,
                 unsigned int def, unsigned int mdef, int rewardGold)
    : Creature(name, hp, 0, agi, atk, matk, def, mdef, 0, 0),
      rewardGold(rewardGold) {}

unsigned int Monster::getRewardGold() const { return rewardGold; }
void Monster::setRewardGold(unsigned int rewardGold) {
  this->rewardGold = rewardGold;
}

MonsterSkill::MonsterSkill() : Skill() {}
MonsterSkill::MonsterSkill(string theName, int theDamageCross)
    : Skill(theName, theDamageCross, 0) {}
void MonsterSkill::addEffect(Effect *eff, target tgt) {
  effects.push_back({eff, tgt});
}

void MonsterSkill::use(vector<Creature *> team, Creature *user) const {
  for (const auto &instance : effects) {
    if (instance.targetType == target::all) {
      for (auto *j : team) {
        if (j && j->isAlive())
          instance.effectPtr->execute(*j);
        user->attack(*j, user->getAtk() * getDamage());
      }
    } else {
      vector<Creature *> alive;
      for (auto *member : team) {
        if (member != nullptr && member->isAlive()) {
          alive.push_back(member);
        }
      }
      if (!alive.empty()) {
        int to = Random::getInt(0, alive.size() - 1);
        instance.effectPtr->execute(*alive[to]);
        user->attack(*alive[to], user->getAtk() * getDamage());
      }
    }
  }
}
void Monster::action(vector<Creature *> team, vector<Creature *> monster) {
  if (!this->isAlive())
    return;

  if (skillBook.empty()) {
    cout << this->getName() << "Do nothing\n";
    return;
  }

  int random_idx = Random::getInt(0, skillBook.size() - 1);

  MonsterSkill *selected_skill = skillBook[random_idx];

  cout << this->getName() << " using: " << selected_skill->getName() << "!\n";

  selected_skill->use(team);
  selected_skill->getDamage();
}

// 讓 addEffect 回傳 *this
MonsterSkill &MonsterSkill::attach(Effect *eff, target tgt) {
  effects.push_back({eff, tgt});
  return *this;
}
// Slime::Slime()
//     : Monster("Slime",
//               {
//                   Skill("撞擊", 30, 0),
//                   Skill(),
//                   Skill(),
//                   Skill(),
//               },
//               0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
// Slime::Slime(string name, unsigned int hp, unsigned int mp, unsigned int agi,
//              unsigned int atk, unsigned int matk, unsigned int def,
//              unsigned int mdef, unsigned int dex, unsigned int luk,
//              int rewardGold)
//     : Monster(name + " Slime", hp, mp, agi, atk, matk, def, mdef, dex, luk,
//               rewardGold) {}
