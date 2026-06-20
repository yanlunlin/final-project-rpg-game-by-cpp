#include "creature.h"
#include "monster.h"
#include "player.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void combat(vector<Player> &team, vector<Monster> &monster) {
  // define
  enum class winner { nobody, team, monster };
  auto notEnd = [&]() -> winner {
    auto check = [](const auto &a) -> bool {
      for (auto i : a) {
        if (i.isAlive()) {
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
    action.push_back(&i);
  }
  for (auto i : monster) {
    action.push_back(&i);
  }

  // main
  do {
    sort(action.begin(), action.end(),
         [](Creature *a, Creature *b) { return a->getAgi() > b->getAgi(); });
    for (auto i : action) {
      i->action();
    }
    endd = notEnd();
  } while (endd == winner::nobody);

  // end
  if (endd == winner::team) {
    for (Monster i : monster) {
      Player::wallet += i.getRewardGold();
    }
  } else {
    cout << "GAME OVER!!!";
    exit(0);
  }
}

// 確認團滅 -> 場地效果 -> 速度排先後 -> 進行行動
