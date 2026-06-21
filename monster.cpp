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
      skillBook(skillBook), rewardGold(rewardGold) {}

unsigned int Monster::getRewardGold() const { return rewardGold; }
void Monster::setRewardGold(unsigned int rewardGold) {
  this->rewardGold = rewardGold;
}
void Monster::showInfo() const {
  cout << getName() << "\t| ";
  cout << "Hp: " << getHp() << "/" << getMaxHp() << "\t| ";
}

MonsterSkill::MonsterSkill() : Skill() {}
MonsterSkill::MonsterSkill(string theName, target tgt, int theDamageCross,
                           vector<Effect *> eff)
    : Skill(theName, theDamageCross, 0), skillTarget(tgt) {}
void MonsterSkill::addEffect(Effect *eff, target tgt) {
  effects.push_back(eff);
}

void MonsterSkill::use(vector<Creature *> team, Creature *user) const {
  vector<Creature *> validTargets;

  if (skillTarget == target::all) {
    for (auto *i : team) {
      if (i && i->isAlive()) {
        validTargets.push_back(i);
      }
    }
  } else {
    vector<Creature *> alive;
    for (auto *member : team) {
      if (member != nullptr && member->isAlive()) {
        alive.push_back(member);
      }
    }
    if (!alive.empty()) {
      validTargets.push_back(alive[Random::getInt(0, alive.size() - 1)]);
    }
  }

  for (auto *i : validTargets) {
    if (getDamage() > 0) {
      int finalDamage = user->getAtk() * getDamage();
      user->attack(*i, finalDamage);
    }
    for (const auto &j : effects) {
      j->execute(*i);
    }
  }
}
void Monster::action(vector<Creature *> team, vector<Creature *> monster) {
  if (!this->isAlive()) {
    return;
  }

  cout << "\n====================================\n";
  cout << "迎接" << this->getName() << "的攻擊!\n";
  cout << "====================================\n";

  if (skillBook.empty()) {
    cout << this->getName() << "Do nothing\n";
    return;
  }

  int random_idx = Random::getInt(0, skillBook.size() - 1);

  MonsterSkill *selected_skill = skillBook[random_idx];

  cout << this->getName() << "使用了" << selected_skill->getName() << "!\n";

  selected_skill->use(team, this);
}

// 讓 addEffect 回傳 *this
MonsterSkill &MonsterSkill::attach(Effect *eff, target tgt) {
  effects.push_back(eff);
  return *this;
}
