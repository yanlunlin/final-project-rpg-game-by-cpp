#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <vector>
using std::string;

class Creature;

class Skill {
private:
  string name;
  int damage;
  int mpCost;

public:
  Skill();
  Skill(string theName, int theDamage, int theMpCost);

  string getName() const;
  int getDamage() const;
  int getMpCost() const;

  void setName(string theName);
  void setDamage(int theDamage);
  void setMpCost(int theMpCost);

  virtual void use(std::vector<Creature *> team) const;
  void showInfo() const;
};

#endif
