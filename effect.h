#include<string>
#include"creature.h"

using std::string;

enum class ValueType{
    Flat,      //固定值
    Percent    //百分比
};

class Effect{
    protected:
        string name;
        string statusTag;
        ValueType valueType;
        int value;
        unsigned int remainingTurns;
    public:
        Effect();
        Effect(string theName, string theTag, ValueType theType, int theValue, unsigned int theRemainingTurns);

        string getName() const;
        string getTag() const;
        ValueType getType() const;
        int getValue() const;
        unsigned int getRemainingTurns() const;

        void setName(string theName);
        void setTag(string theTag);
        void setType(ValueType theType);
        void setValue(int theValue);
        void setRemainingTurns(unsigned int theRemainingTurns);

        void execute(Creature& target);
};

class Heal: public Effect{
    public:
        Heal();
        Heal(ValueType theType, int theValue, unsigned int theRemainingTurns);
};

class Poison: public Effect{
    public:
        Poison();
        Poison(ValueType theType, int theValue, unsigned int theRemainingTurns);
};