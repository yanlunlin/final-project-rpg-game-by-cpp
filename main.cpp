#include "monster.h"
#include "skill.h"
#include <vector>

using namespace std;

int main() {
  Heal heal;
  Poison poison;
  vector<MonsterSkill *> slimeSkillBook = {
      new MonsterSkill("撞擊", 1),
  };
  Monster slime("slime", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
}

// #include <iostream>
// #include <vector>
//
// #include "skill.h"
// #include "creature.h"
// #include "player.h"
// #include "monster.h"
// #include "item.h"
// #include "inventory.h"
// #include "weapon.h"
// #include "potion.h"
//
// using namespace std;
//
// int main() {
//     cout << "===== Skill Test =====" << endl;
//     Skill fireBall("Fire Ball", 50, 20);
//     fireBall.showInfo();
//     cout << "getDamage(): " << fireBall.getDamage() << endl;
//     cout << "getMpCost(): " << fireBall.getMpCost() << endl;
//     fireBall.use();
//
//     cout << "\n===== Creature Test =====" << endl;
//     Creature base("Base Creature", 100, 30, 10, 12, 8, 5, 4, 6, 3);
//     base.showInfo();
//     base.takeDamage(25);
//     cout << "After taking 25 damage:" << endl;
//     base.showInfo();
//     cout << "isAlive(): " << (base.isAlive() ? "true" : "false") << endl;
//
//     cout << "\n===== Player Test =====" << endl;
//     Player hero;
//     hero.setName("Hero");
//     hero.setHp(120);
//     hero.setMp(40);
//     hero.setAgi(10);
//     hero.setAtk(15);
//     hero.setMatk(8);
//     hero.setDef(6);
//     hero.setMdef(4);
//     hero.setDex(7);
//     hero.setLuk(3);
//     hero.showInfo();
//     cout << "Hero alive? " << (hero.isAlive() ? "true" : "false") << endl;
//
//     cout << "\n===== Monster Test =====" << endl;
//     Monster slime("Green", 60, 8, 20, 0, 0, 0, 0, 0, 0, 100);
//     slime.showInfo();
//     cout << "Reward gold: " << slime.getRewardGold() << endl;
//     cout << "Slime alive? " << (slime.isAlive() ? "true" : "false") << endl;
//
//     cout << "\n===== Battle Test =====" << endl;
//     hero.attack(slime);
//     cout << "After Hero attacks Slime:" << endl;
//     slime.showInfo();
//
//     slime.attack(hero);
//     cout << "After Slime attacks Hero:" << endl;
//     hero.showInfo();
//
//     cout << "\n===== Item / Weapon / Potion Test =====" << endl;
//     Weapon ironSword("Iron Sword", 10, 2);
//     Potion healingPotion("Healing Potion", "hp", 25, 3);
//
//     ironSword.showInfo();
//     healingPotion.showInfo();
//
//     cout << "Use sword: " << (ironSword.use() ? "success" : "fail") << endl;
//     cout << "Use potion: " << (healingPotion.use() ? "success" : "fail") <<
//     endl;
//
//     cout << "After using items:" << endl;
//     ironSword.showInfo();
//     healingPotion.showInfo();
//
//     cout << "\n===== Inventory Test =====" << endl;
//     vector<Item> bag = { healingPotion, ironSword };
//     Inventory inv(5, bag);
//     cout << "Inventory max size: " << inv.getMaxSize() << endl;
//     cout << "Inventory item count: " << inv.getStorage().size() << endl;
//
//     if (!inv.getStorage().empty()) {
//         cout << "First item before use:" << endl;
//         inv.getStorage()[0].showInfo();
//         inv.useItem(0);
//         cout << "First item after use:" << endl;
//         inv.getStorage()[0].showInfo();
//     }
//
//     cout << "\n===== End of Test =====" << endl;
//     return 0;
// }
