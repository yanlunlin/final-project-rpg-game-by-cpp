#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<map>
#include<vector>
#include"creature.h"
#include"inventory.h"
#include"item.h"

using std::string;
using std::map;
using std::vector;

class Monster;

class Player: public Creature{
    private:
        /*map<string, unsigned int> status{
            {"hp", 0}, {"mp", 0}, {"str", 0}, {"vit", 0}, {"agi", 0}, {"dex", 0}, {"int", 0}
        };*/

        /*map<string, unsigned int> status{
            {"hp", 0}, {"mp", 0},
            {"agi", 0}, //agility 敏捷
            {"atk", 0}, {"matk", 0},
            {"def", 0}, {"mdef", 0},
            {"dex", 0}, //dexterity 影響暴擊率及命中率, 影響命中率較多
            {"luk", 0}, //luck 影響暴擊率及命中率, 影響暴擊率較多
        }*/

        Inventory backpack;
    public:
        Player();
        Player(string theName, int theHp, int theAttackPower);

        const Inventory& getBackpack() const;
        const vector<Item>& getItemList() const;

        /*void attack(Monster& target);
        void takeDamage(const Monster& attacker, int damage);*/
        void useItem(size_t index);
};

class Swordman: public Player{
    public:
        Swordman();
        Swordman(string theName, int theHp, int theAttackPower);
};

class SwordMaster: public Swordman{
    public:
        SwordMaster();
        SwordMaster(string theName, int theHp, int theAttackPower);
};

class Warrior: public Player{
    public:
        Warrior();
        Warrior(string theName, int theHp, int theAttackPower);
};

class Crusader: public Warrior{
    public:
        Crusader();
        Crusader(string theName, int theHp, int theAttackPower);
};

class Wizard: public Player{
    public:
        Wizard();
        Wizard(string theName, int theHp, int theAttackPower);
};

class ArchWizard: public Wizard{
    public:
        ArchWizard();
        ArchWizard(string theName, int theHp, int theAttackPower);
};

class Priest: public Player{
    public:
        Priest();
        Priest(string theName, int theHp, int theAttackPower);
};

class ArchPriest: public Priest{
    public:
        ArchPriest();
        ArchPriest(string theName, int theHp, int theAttackPower);
};

class Archer: public Player{
    public:
        Archer();
        Archer(string theName, int theHp, int theAttackPower);
};

class Thief: public Player{
    public:
        Thief();
        Thief(string theName, int theHp, int theAttackPower);
};

class Assassin: public Thief{
    public:
        Assassin();
        Assassin(string theName, int theHp, int theAttackPower);
};

#endif