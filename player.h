#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<map>
#include<vector>
#include"inventory.h"
#include"item.h"

using std::string;
using std::map;
using std::vector;

class Monster;

class Player{
    private:
        string name;
        /*map<string, unsigned int> status{
            {"hp", 0}, {"mp", 0}, {"str", 0}, {"vit", 0}, {"agi", 0}, {"dex", 0}, {"int", 0}
        };*/
        int hp;
        int attackPower;
        Inventory backpack;
    public:
        Player();
        Player(string theName, int theHp, int theAttackPower);

        string getName() const;
        int getHp() const;
        int getAttackPower() const;
        const Inventory& getBackpack() const;
        const vector<Item>& getItemList() const;

        void setName(string theName);
        void setHp(int theHp);
        void setAttackPower(int theAttackPower);

        void attack(Monster& target);
        void takeDamage(const Monster& attacker, int damage);
        void useItem(size_t index);

        bool isAlive();
};

class Swordman: public Player{
    public:
        Swordman();
        Swordman(string theName, int theHp, int theAttackPower);
};

#endif