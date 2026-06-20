#include<string>
#include"effect.h"
#include"creature.h"

using std::string;

Effect::Effect(): name(""), valueType(ValueType::Flat), value(0), remainingTurns(0){}
Effect::Effect(string theName, ValueType theType, int theValue, unsigned int theRemainingTurns): name(theName), valueType(theType), value(theValue), remainingTurns(theRemainingTurns){}

string Effect::getNmae() const{
    return name;
}

ValueType Effect::getType() const{
    return valueType;
}

int Effect::getValue() const{
    return value;
}

unsigned int Effect::getRemainingTurns() const{
    return remainingTurns;
}

void Effect::setName(string theName){
    name = theName;
}

void Effect::setType(ValueType theType){
    valueType = theType;
}

void Effect::setValue(int theValue){
    value = theValue;
}

void Effect::setRemainingTurns(unsigned int theRemainingTurns){
    remainingTurns = theRemainingTurns;
}

void Effect::execute(Creature& target){
    if(remainingTurns > 0){}
}

Heal::Heal(): Effect("heal", ValueType::Flat, 0, 0){}
Heal::Heal(ValueType theType, int theValue, unsigned int theRemainingTurns): Effect("heal", theType, theValue, theRemainingTurns){}

Poison::Poison(): Effect("poison", ValueType::Flat, 0, 0){}
Poison::Poison(ValueType theType, int theValue, unsigned int theRemainingTurns): Effect("poison", theType, theValue, theRemainingTurns){}