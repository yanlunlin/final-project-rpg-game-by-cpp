#include<string>
#include"effect.h"
#include"creature.h"

using std::string;

Effect::Effect(): name(""), statusTag(""), valueType(ValueType::Flat), value(0), remainingTurns(0){}
Effect::Effect(string theName, string theTag, ValueType theType, int theValue, unsigned int theRemainingTurns): name(theName), statusTag(theTag), valueType(theType), value(theValue), remainingTurns(theRemainingTurns){}

string Effect::getName() const{
    return name;
}

string Effect::getTag() const{
    return statusTag;
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

void Effect::setTag(string theTag){
    statusTag = theTag;
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
    if(remainingTurns > 0){
        int finalValue = 0;

        if(valueType == ValueType::Flat){
            finalValue = value;
        }else if(valueType == ValueType::Percent){
            unsigned int baseValue = 0;

            if(statusTag == "hp"){
                baseValue = target.getMaxHp();
            }else if(statusTag == "mp"){
                baseValue = target.getMaxMp();
            }else{
                baseValue = target.getStatBase(statusTag);
            }

            finalValue = static_cast<int>(baseValue*(value/100.0));
        }

        if(statusTag == "hp"){
            if(value >= 0){
                target.heal(static_cast<unsigned int>(finalValue));
            }else{
                target.takeDamage(static_cast<unsigned int>(-finalValue));
            }
        }else if(statusTag == "mp"){
            if(value >= 0){
                target.healMp(static_cast<unsigned int>(finalValue));
            }else{
                target.loseMp(static_cast<unsigned int>(-finalValue));
            }
        }else{
            if(valueType == ValueType::Flat){
                target.addBonusFlat(statusTag, value);
            }else if(valueType == ValueType::Percent){
                target.addBonusPercent(statusTag, value);
            }
        }

        remainingTurns--;
    }
}

/*Heal::Heal(): Effect("heal", "hp", ValueType::Flat, 0, 0){}
Heal::Heal(ValueType theType, int theValue, unsigned int theRemainingTurns): Effect("heal", "hp", theType, theValue, theRemainingTurns){}

Poison::Poison(): Effect("poison", "hp", ValueType::Flat, 0, 0){}
Poison::Poison(ValueType theType, int theValue, unsigned int theRemainingTurns): Effect("poison", "hp", theType, theValue, theRemainingTurns){}*/