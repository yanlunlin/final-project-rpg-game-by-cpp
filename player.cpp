#include<string>
#include"player.h"
#include"monster.h"

using std::string;
using std::vector;

Player::Player(){}
Player::Player(string theName, int theHp, int theAttackPower){}

string Player::getName() const{
    return name;
}

int Player::getHp() const{
    return hp;
}

int Player::getAttackPower() const{
    return attackPower;
}

const Inventory& Player::getBackpack() const{
    return backpack;
}

const vector<Item>& Player::getItemList() const{
    return backpack.getStorage();
}

void Player::setName(string theName){
    name = theName;
}

void Player::setHp(int theHp){
    hp = (theHp < 0) ? 0 : theHp;
}

void Player::setAttackPower(int theAttackPower){
    attackPower = (theAttackPower < 0) ? 0 : theAttackPower;
}

void Player::attack(Monster& target){
    target.takeDamage(*this, getAttackPower());
}

void Player::takeDamage(const Monster& attacker, int damage){
    setHp(hp - damage);
}

void Player::useItem(size_t index){
    backpack.useItem(index);
}

bool Player::isAlive(){
    return (hp > 0) ? false : true;
}