#ifndef PLAYER_H
#define PLAYER_H

#include<string>
//#include"item.h"

using std::string;

class Player{
    private:
        string name;
        int hp;
        int attackPower;
        //Item item;
    public:
        Player();

        string getName();
        int getHp();
        int getAttackPower();

        void setName(string);
        void setHp(int);
        void setAttackPower(int);

        void attack();
        void takeDamage();
        void useItem();
        bool isAlive();
};

class Swordman: public Player{

};

#endif