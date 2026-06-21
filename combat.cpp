#include "creature.h"
#include "monster.h"
#include "player.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void combat(vector<Creature *> &team, vector<Creature *> &monster) {
  // define
  enum class winner { nobody, team, monster };
  auto notEnd = [&]() -> winner {
    auto check = [](const auto &a) -> bool {
      for (auto i : a) {
        if (i->isAlive()) {
          return 1;
        }
      }
      return 0;
    };
    bool x = check(team), y = check(monster);
    if (x && y) {
      return winner::nobody;
    } else {
      return x ? winner::team : winner::monster;
    }
  };
  winner endd;
  vector<Creature *> action;
  for (auto i : team) {
    action.push_back(i);
  }
  for (auto i : monster) {
    action.push_back(i);
  }

  // main
  do {
    for (auto i : team) {
      cout << i->getName() << " Hp: " << i->getHp() << endl;
    }
    for (auto i : monster) {
      cout << i->getName() << " Hp: " << i->getHp() << endl;
    }
    sort(action.begin(), action.end(),
         [](Creature *a, Creature *b) { return a->getAgi() > b->getAgi(); });
    for (auto i : action) {
      i->action(team, monster);
      endd = notEnd();
      if (endd != winner::nobody) {
        break;
      }
    }
  } while (endd == winner::nobody);

  // end
  if (endd == winner::team) {
    cout << endl;
    cout << "戰鬥結束 (按 Enter 繼續)" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cout << "\033[2J\033[1;1H";

    for (auto i : monster) {
      Player::wallet += static_cast<Monster *>(i)->getRewardGold();
      cout << "你獲得了金幣!!!" << endl
           << "你有" << Player::wallet << "個金幣!";
    }
  } else {
    cout << "GAME OVER!!!";
    exit(0);
  }
}

// 確認團滅 -> 場地效果 -> 速度排先後 -> 進行行動