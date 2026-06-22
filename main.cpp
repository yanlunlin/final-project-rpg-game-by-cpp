#define WIN32_LEAN_AND_MEAN
#include "combat.h"
#include "effect.h"
#include "monster.h"
#include "player.h"
#include "skill.h"
#include "item.h"
#include "potion.h"
#include <windows.h>
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
  cout << "\n\n\n=====================================\n";
  cout << "          隊伍招募畫面\n";
  cout << "=====================================\n\n";

  vector<Player *> allAgent =
  {new Swordman("劍士"), new Warrior("戰士"), new Wizard("法師"),   new Priest("祭司"), new Archer("弓箭手"), new Thief("盜賊")};

  cout << "可招募角色：\n\n";

  for (int i = 0; i < allAgent.size(); i++)
  {
    cout << "[" << i << "] ";
    allAgent[i]->showInfo();
    cout << "-----------------------------------------------\n";
  }

  vector<Creature *> team;

  cout << "\n請選擇 4 位隊員組成冒險隊伍。\n\n";

  for (int i = 0; i < 4; i++)
  {
    int choice = -1;
    cout << "請招募第 " << (i + 1) << " 位隊員 (輸入代號 0~5)：";
    cin >> choice;

    // 輸入驗證
    if (cin.fail() || choice < 0 || choice >= allAgent.size())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "\n輸入錯誤，請重新選擇。\n\n";
      i--;
      continue;
    }
    Player *newMember = nullptr;
    switch (choice) {
        case 0:newMember = new Swordman("劍士"); break;
        case 1:newMember = new Warrior("戰士"); break;
        case 2:newMember = new Wizard("法師"); break;
        case 3:newMember = new Priest("祭司"); break;
        case 4:newMember = new Archer("弓箭手"); break;
        case 5:newMember = new Thief("盜賊"); break;
    }
    team.push_back(newMember);

    Potion redPotion("回血藥水", "hp", ValueType::Flat, 10, 1, 1);
    newMember->addItem(redPotion);

    cout << "成功招募！\n\n";
  }

  // 清畫面
  cout << "\033[2J\033[1;1H";

  // 第一關劇情
  cout << "\n\n\n=====================================\n";
  cout << "            第一關\n";
  cout << "          新手森林\n";
  cout << "=====================================\n\n";

  cout << "隊伍進入森林後，發現一隻奇怪的魔物。\n";
  cout << "牠看起來黏黏的，而且充滿敵意。\n\n";

  cout << "史萊姆出現了！\n\n";

  // 怪物技能
  vector<MonsterSkill *> slimeSkillBook =
    {new MonsterSkill("撞擊", MonsterSkill::target::player, 1, {new Effect(),}),
    new MonsterSkill("緩速", MonsterSkill::target::player, 0, {new Effect("緩速", "agi", ValueType::Flat, -5, 3),})};

  // 建立怪物
  Monster *slime = new Monster("史萊姆", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
  vector<Creature *> monsters;
  for (int i = 0; i < 2; i++)
  {
    Monster *newMonster = nullptr;
    newMonster = new Monster("史萊姆", slimeSkillBook, 50, 15, 15, 0, 15, 0, 5);
    monsters.push_back(newMonster);
  }

  cout << "戰鬥開始！\n\n";

  // 戰鬥系統
  combat(team, monsters);

  cout << "\n\n=====================================\n";
  cout << "            第二關\n";
  cout << "         史萊姆巢穴深處\n";
  cout << "=====================================\n\n";

  cout << "就在你們擊敗普通史萊姆後...\n";
  cout << "整個地面開始劇烈震動！\n";
  cout << "大量史萊姆融合成一個巨大的身影！\n\n";

  cout << "【魔王】巨大史萊姆 King Slime 出現了！\n\n";

  cout << "按 Enter 開始最終決戰...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();

  cout << "\033[2J\033[1;1H";

  vector<MonsterSkill*> bossSkillBook =
{
    new MonsterSkill(
        "泰山壓頂",
        MonsterSkill::target::player,
        1,
        {
            new Effect()
        }
    ),

    new MonsterSkill(
        "黏液束縛",
        MonsterSkill::target::player,
        0,
        {
            new Effect(
                "重度緩速",
                "agi",
                ValueType::Flat,
                -15,
                5
            )
        }
    ),

    new MonsterSkill(
        "王者怒吼",
        MonsterSkill::target::player,
        0,
        {
            new Effect(
                "恐懼",
                "atk",
                ValueType::Percent,
                -30,
                3
            )
        }
    )
};

Monster* kingSlime =
    new Monster(
        "巨大史萊姆王",
        bossSkillBook,
        500,    // HP
        100,    // MP
        25,     // AGI
        40,     // ATK
        30,     // MATK
        20,     // DEF
        20      // MDEF
    );
  vector<Creature*> bossStage;

  bossStage.push_back(kingSlime);

  cout << "\n最終戰開始！\n\n";

  combat(team, bossStage);

  // 戰鬥結束
  cout << "\n=====================================\n";
  cout << "           戰鬥結束\n";
  cout << "=====================================\n";

  cout << "\n=====================================\n";
  cout << "          恭喜破關！\n";
  cout << "=====================================\n";

  cout << "巨大史萊姆王被擊敗了！\n";
  cout << "米德加爾特再次恢復和平。\n";
  cout << "你與夥伴成為了傳說中的英雄！\n";

  cout << "\n感謝遊玩！\n";

  return 0;
}