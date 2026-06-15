#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<vector>
#include"item.h"
#include"monster.h"

using std::string;

class Player{
    private:
        string name;
        int hp;
        int attackPower;
        vector<Item> item;
    public:
        Player();
        Player(string theName, int theHp, int theAttackPower);

        string getName() const;
        int getHp() const;
        int getAttackPower() const;
        const vector<Item>& getItem() const;

        void setName(string theName);
        void setHp(int theHp);
        void setAttackPower(int theAttackPower);

        void attack(Monster& target);
        void takeDamage(const Monster& attacker);
        void useItem(int index);

        bool isAlive();
};

class Swordman: public Player{

};

#endif