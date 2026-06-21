#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "combat.h"
#include "effect.h"
#include "monster.h"
#include "player.h"
#include "skill.h"

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    // 啟用 UTF-8，避免中文亂碼
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 遊戲開場
    cout << "=====================================\n";
    cout << "      米德加爾特保衛戰 RPG\n";
    cout << "=====================================\n";
    cout << "魔物正在入侵米德加爾特大陸。\n";
    cout << "你必須組建一支冒險隊伍，擊敗來襲的怪物。\n\n";

    cout << "按 Enter 開始遊戲...";
    cin.get();

    cout << "\033[2J\033[1;1H";

    // 招募隊伍
    cout << "=====================================\n";
    cout << "          隊伍招募畫面\n";
    cout << "=====================================\n\n";

    vector<Player*> allAgent = {
        new Swordman("劍士"),
        new Warrior("戰士"),
        new Wizard("法師"),
        new Priest("祭司"),
        new Archer("弓箭手"),
        new Thief("盜賊")
    };

    cout << "可招募角色：\n\n";

    for (int i = 0; i < allAgent.size(); i++) {
        cout << "[" << i << "] ";
        allAgent[i]->showInfo();
        cout << "------------------------\n";
    }

    vector<Creature*> team;

    cout << "\n請選擇 4 位隊員組成冒險隊伍。\n\n";

    for (int i = 0; i < 4; i++) {

        int choice = -1;

        cout << "請招募第 "
             << (i + 1)
             << " 位隊員 (輸入代號 0~5)：";

        cin >> choice;

        // 輸入驗證
        if (cin.fail() ||
            choice < 0 ||
            choice >= allAgent.size()) {

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\n輸入錯誤，請重新選擇。\n\n";

            i--;
            continue;
        }

        Player* newMember = nullptr;

        switch (choice) {
        case 0:
            newMember = new Swordman("劍士");
            break;

        case 1:
            newMember = new Warrior("戰士");
            break;

        case 2:
            newMember = new Wizard("法師");
            break;

        case 3:
            newMember = new Priest("祭司");
            break;

        case 4:
            newMember = new Archer("弓箭手");
            break;

        case 5:
            newMember = new Thief("盜賊");
            break;
        }

        team.push_back(newMember);

        cout << "成功招募！\n\n";
    }

    // 清畫面
    cout << "\033[2J\033[1;1H";

    // =============================
    // 第一關劇情
    // =============================

    cout << "=====================================\n";
    cout << "            第一關\n";
    cout << "          新手森林\n";
    cout << "=====================================\n\n";

    cout << "隊伍進入森林後，發現一隻奇怪的魔物。\n";
    cout << "牠看起來黏黏的，而且充滿敵意。\n\n";

    cout << "史萊姆出現了！\n\n";

    // =============================
    // 怪物技能
    // =============================

    vector<MonsterSkill*> slimeSkillBook = {

        new MonsterSkill(
            "撞擊",
            MonsterSkill::target::player,
            1,
            {
                new Effect(),
            }
        ),

        new MonsterSkill(
            "緩速",
            MonsterSkill::target::player,
            0,
            {
                new Effect(
                    "緩速",
                    "agi",
                    ValueType::Flat,
                    -5,
                    3
                ),
            }
        )
    };

    // =============================
    // 建立怪物
    // =============================

    Monster* slime =
        new Monster(
            "史萊姆",
            slimeSkillBook,
            50,  // HP
            15,  // MP
            15,  // AGI
            0,   // ATK
            15,  // MATK
            0,   // DEF
            5    // MDEF
        );

    vector<Creature*> monsters;
    monsters.push_back(slime);

    cout << "戰鬥開始！\n\n";

    // =============================
    // 戰鬥系統
    // =============================

    combat(team, monsters);

    // =============================
    // 戰鬥結束
    // =============================

    cout << "\n=====================================\n";
    cout << "           戰鬥結束\n";
    cout << "=====================================\n";

    cout << "\n感謝遊玩！\n";

    return 0;
}

// #define WIN32_LEAN_AND_MEAN
// #include <windows.h>

// #include "combat.h"
// #include "effect.h"
// #include "monster.h"
// #include "player.h"
// #include "skill.h"
// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//   SetConsoleOutputCP(CP_UTF8); 
//   SetConsoleCP(CP_UTF8);

//   cout << "Game Start (Press Enter)" << endl;
//   cin.get();
//   cout << "\033[2J\033[1;1H";

//   cout << "Choose your team member> \n";
//   vector<Player *> allAgent = {
//       new Swordman("Swordman"), new Warrior("Warrior"), new Wizard("Wizard"),
//       new Priest("Priest"),     new Archer("Archer"),   new Thief("Thief"),
//   };
//   for (int i = 0; i < allAgent.size(); i++) {
//     cout << "[" << i << "] ";
//     allAgent[i]->showInfo();
//   }

//   vector<Creature *> team;

//   for (int i = 0; i < 4; i++) {
//     int choice = -1;
//     cout << "請招募第 " << (i + 1) << " 位隊員 (輸入代號 0-5): ";
//     cin >> choice;

//     // 🛡️ 結合我們剛學的 cin 防呆機制
//     if (cin.fail() || choice < 0 || choice >= allAgent.size()) {
//       cin.clear();
//       cin.ignore(numeric_limits<streamsize>::max(), '\n');
//       cout << "Error Input\n";
//       i--; // 讓這回合重跑一次
//       continue;
//     }

//     Player *newMember = nullptr;
//     switch (choice) {
//     case 0:
//       newMember = new Swordman("Swordman");
//       break;
//     case 1:
//       newMember = new Warrior("Warrior");
//       break;
//     case 2:
//       newMember = new Wizard("Wizard");
//       break;
//     case 3:
//       newMember = new Priest("Priest");
//       break;
//     case 4:
//       newMember = new Archer("Archer");
//       break;
//     case 5:
//       newMember = new Thief("Thief");
//       break;
//     }

//     team.push_back(newMember);
//   }

//   cout << "\033[2J\033[1;1H";
//   cout << "進入戰鬥 \n";
//   vector<MonsterSkill *> slimeSkillBook = {
//       new MonsterSkill("撞擊", MonsterSkill::target::player, 1,
//                        {
//                            new Effect(),
//                        }),
//       new MonsterSkill("緩速", MonsterSkill::target::player, 0,
//                        {
//                            new Effect("緩速", "agi", ValueType::Flat, -5, 3),
//                        }),
//   };

//   Monster *slime =
//       new Monster("史萊姆", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
//   vector<Creature *> monsters;
//   monsters.push_back(slime);

//   combat(team, monsters);
// }
