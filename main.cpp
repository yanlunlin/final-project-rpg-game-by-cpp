#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "combat.h"
#include "effect.h"
#include "monster.h"
#include "player.h"
#include "skill.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  SetConsoleOutputCP(CP_UTF8); 
  SetConsoleCP(CP_UTF8);

  cout << "Game Start (Press Enter)" << endl;
  cin.get();
  cout << "\033[2J\033[1;1H";

  cout << "Choose your team member> \n";
  vector<Player *> allAgent = {
      new Swordman("Swordman"), new Warrior("Warrior"), new Wizard("Wizard"),
      new Priest("Priest"),     new Archer("Archer"),   new Thief("Thief"),
  };
  for (int i = 0; i < allAgent.size(); i++) {
    cout << "[" << i << "] " << allAgent[i]->getName() << endl;
  }

  vector<Creature *> team;

  for (int i = 0; i < 4; i++) {
    int choice = -1;
    cout << "請招募第 " << (i + 1) << " 位隊員 (輸入代號 0-5): ";
    cin >> choice;

    // 🛡️ 結合我們剛學的 cin 防呆機制
    if (cin.fail() || choice < 0 || choice >= allAgent.size()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error Input\n";
      i--; // 讓這回合重跑一次
      continue;
    }

    Player *newMember = nullptr;
    switch (choice) {
    case 0:
      newMember = new Swordman("Swordman");
      break;
    case 1:
      newMember = new Warrior("Warrior");
      break;
    case 2:
      newMember = new Wizard("Wizard");
      break;
    case 3:
      newMember = new Priest("Priest");
      break;
    case 4:
      newMember = new Archer("Archer");
      break;
    case 5:
      newMember = new Thief("Thief");
      break;
    }

    team.push_back(newMember);
  }

  cout << "\033[2J\033[1;1H";
  cout << "進入戰鬥 \n";
  vector<MonsterSkill *> slimeSkillBook = {
      new MonsterSkill("撞擊", MonsterSkill::target::player, 1,
                       {
                           new Effect(),
                       }),
      new MonsterSkill("緩速", MonsterSkill::target::player, 0,
                       {
                           new Effect("緩速", "agi", ValueType::Flat, -5, 3),
                       }),
  };

  Monster *slime =
      new Monster("史萊姆", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
  vector<Creature *> monsters;
  monsters.push_back(slime);

  combat(team, monsters);
}

//   cout << "=== 系統初始化中 ===\n";
//
//   // 1. 建立史萊姆的技能書與史萊姆本體
//   vector<MonsterSkill *> slimeSkillBook = {
//       new MonsterSkill("撞擊", MonsterSkill::target::player, 1,
//                        {
//                            new Effect(),
//                        }),
//       new MonsterSkill("緩速", MonsterSkill::target::player, 0,
//                        {
//                            new Effect("緩速", "agi", ValueType::Flat, -5,
//                            3),
//                        }),
//   };
//
//   // 🎯 這裡一定要用 new，因為你的 combat 容器是裝指標 Creature*
//   Monster *slime =
//       new Monster("史萊姆", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
//
//   // 2. 建立玩家測試機體 (這裡的參數請替換成你 Player 實際的建構子)
//   // 假設依序為：名字, HP, MP, AGI, ATK, MATK, DEF, MDEF
//   Player *hero = new Swordman("超強劍士");
//
//   // 3. 建立並配置陣營隊伍
//   vector<Creature *> player_team;
//   player_team.push_back(hero);
//
//   vector<Creature *> monster_team;
//   monster_team.push_back(slime);
//
//   // 4. 戰鬥前情提要
//   cout << "\n⚔️ 戰鬥開始！\n";
//   cout << hero->getName() << " (HP: " << hero->getHp()
//        << ", AGI: " << hero->getAgi() << ") VS ";
//   cout << slime->getName() << " (HP: " << slime->getHp()
//        << ", AGI: " << slime->getAgi() << ")\n";
//   cout << "------------------------------------\n";
//
//   // 5. 進入核心戰鬥迴圈
//   combat(player_team, monster_team);
//
//   // 6. 戰鬥結束後的驗證
//   cout << "------------------------------------\n";
//   cout << "🎉 戰鬥結束！結算畫面：\n";
//   cout << "目前玩家金幣 (Player::wallet): " << Player::wallet << " G\n";
//   cout << hero->getName() << " 剩餘 HP: " << hero->getHp() << "\n";
// }

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
//     cout << "Slime alive? " << (slime.isAlive() ? "true" : "false") <<
//     endl;
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
//     cout << "Use sword: " << (ironSword.use() ? "success" : "fail") <<
//     endl; cout << "Use potion: " << (healingPotion.use() ? "success" :
//     "fail") << endl;
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
//     return 0
