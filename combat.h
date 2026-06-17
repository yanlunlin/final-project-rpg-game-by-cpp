#pragma once
#include "monster.h"
#include "player.h"
#include <vector>
using namespace std;

class Combat {
private:
  vector<Player> player;
  vector<Monster> monster;
  template <typename T> bool checkAnyoneAlive(T a) {
    for (auto i : a) {
      if (i.isAlive()) {
        return 0;
      }
    }
    return 1;
  }

public:
  bool checkEnd();
  bool fight();
};
