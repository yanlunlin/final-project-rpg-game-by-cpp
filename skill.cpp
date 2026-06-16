#include "skill.h"
#include <iostream>
using namespace std;

//constructors
Skill::Skill() : name("Unknown Skill"), damage(0), mpCost(0){}
Skill::Skill(string theName, int theDamage, int theMpCost) : name(theName), damage(theDamage), mpCost(theMpCost){}

//get functions
string Skill::getName() const{return name;}
int Skill::getDamage() const{return damage;}
int Skill::getMpCost() const{return mpCost;}

//set functions
void Skill::setName(string theName){name = theName;}
void Skill::setDamage(int theDamage){damage = (theDamage < 0) ? 0 : theDamage;}
void Skill::setMpCost(int theMpCost){mpCost = (theMpCost < 0) ? 0 : theMpCost;}

//use the skill
void Skill::use() const{cout << name << " deals " << damage << " damage!" << endl;}

//display skills info
void Skill::showInfo() const
{
    cout << "Skill: " << name << endl;
    cout << "Damage: " << damage << endl;
    cout << "MP Cost: " << mpCost << endl;
}