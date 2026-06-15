#include<string>
#include"player.h"
#include"monster.h"

using std::string;

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

const vector<Item>& Player::getItem() const{
    return item;
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
    target.takeDamage(*this);
}

void Player::takeDamage(const Monster& attacker){
    setHp(hp - attacker.getAttackPower());
}

void Player::useItem(int index){
    item[index].use();
}

bool Player::isAlive(){
    return (hp > 0) ? false : true;
}