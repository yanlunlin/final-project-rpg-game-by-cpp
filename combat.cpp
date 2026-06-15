#include "combat.h"

bool Combat::checkEnd() {
  checkAnyoneAlive(player);
  checkAnyoneAlive(monster);
}
