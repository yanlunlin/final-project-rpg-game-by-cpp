#include<string>
#include"player.h"
#include"monster.h"

using std::string;
using std::vector;

Player::Player(){}
Player::Player(string theName, int theHp, int theAttackPower){}

const Inventory& Player::getBackpack() const{
    return backpack;
}

const vector<Item>& Player::getItemList() const{
    return backpack.getStorage();
}

/*void Player::attack(Monster& target){
    target.takeDamage(getAttackPower());
}

void Player::takeDamage(const Monster& attacker, int damage){
    setHp(hp - damage);
}*/

void Player::useItem(size_t index){
    backpack.useItem(index);
}