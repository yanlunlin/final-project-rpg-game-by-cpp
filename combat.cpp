#include "combat.h"
#include <vector>

bool Combat::checkEnd() {
  return checkAnyoneAlive(player) && checkAnyoneAlive(monster);
}

bool Combat::fight() {
  if (checkEnd()) {
    return 1;
  }
}

// 確認團滅 -> 場地效果 -> 速度排先後 -> 進行行動
