#include<string>
#include<iostream>
#include"player.h"
#include"monster.h"
#include"inventory.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

Player::Player(): Creature(), backpack(){}
Player::Player(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Creature(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk), backpack(5){}

const Inventory& Player::getBackpack() const{
    return backpack;
}

const vector<Item>& Player::getItemList() const{
    return backpack.getStorage();
}

void Player::addActiveEffect(const Effect& theEffect){
    for(size_t i = 0; i < activeEffect.size(); ++i){
        if(activeEffect[i].getName() == theEffect.getName()){
            
            unsigned int maxTurns = std::max(activeEffect[i].getRemainingTurns(), theEffect.getRemainingTurns());
            activeEffect[i].setRemainingTurns(maxTurns);

            return;
        }
    }

    activeEffect.push_back(theEffect);
}

void Player::updateEffects(){
    for(auto it = activeEffect.begin(); it != activeEffect.end(); ){
        
        it->execute(*this);

        unsigned int currentTurns = it->getRemainingTurns();
        if(currentTurns > 0){
            it->setRemainingTurns(currentTurns - 1);
        }

        if(it->getRemainingTurns() == 0){
            it = activeEffect.erase(it);
        }else{
            ++it;
        }
    }
}

/*void Player::attack(Monster& target){
    target.takeDamage(getAttackPower());
}

void Player::takeDamage(const Monster& attacker, int damage){
    setHp(hp - damage);
}*/

void Player::useItem(size_t index){
    if(index >= backpack.getSize()){
        return;
    }

    string itemType = backpack.getItem(index).getType();

    if(itemType == "Potion"){
        Item* potionPtr = backpack.usePotion(index);
        if(potionPtr != nullptr){
            this->addActiveEffect(potionPtr->getEffect());
            cout << name << " 喝下了 【" << potionPtr->getName() << "】！" << endl;
        }
        
        if(backpack.getItem(index).getQuantity() == 0){
            backpack.removeItem(index);
        }
    }else if(itemType == "Weapon" || itemType == "Equipment"){
        this->changeEquipment(index);
    }
}

void Player::action(vector<Creature*> team, vector<Creature*> monsters){
    if(!this->isAlive()){
        return;
    }

    cout << "\n====================================\n";
    cout << "It's " << this->getName() << "'s turn!\n";
    cout << "====================================\n";

    if(skillBook.empty()){
        cout << this->getName() << " doesn't know any skills and can only wait...\n";
        return;
    }

    cout << "Choose a skill to use:\n";
    for(size_t i = 0; i < skillBook.size(); ++i){
        cout << "[" << i << "] " << skillBook[i].getName() << "\n";
    }

    int skillChoice = -1;

    while(true){
        cout << "Enter skill number: ";
        cin >> skillChoice;

        if(cin.fail() || skillChoice < 0 || skillChoice >= skillBook.size()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid selection. Please try again.\n";
        }else{
            break;
        }
    }

    PlayerSkill& selectedSkill = skillBook[skillChoice];

    Creature* selectedTarget = nullptr;

    cout << "\nChoose a target:\n";
    for(size_t i = 0; i < monsters.size(); ++i){
        if(monsters[i] && monsters[i]->isAlive()){
            cout << "[" << i << "] " << monsters[i]->getName() << " (HP: " << monsters[i]->getHp() << "/" << monsters[i]->getMaxHp() << ")\n";
        }
    }

    int targetChoice = -1;
    while(true){
        cout << "Enter target number: ";
        cin >> targetChoice;

        if(cin.fail() || targetChoice < 0 || targetChoice >= monsters.size() || monsters[targetChoice] == nullptr || !monsters[targetChoice]->isAlive()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid target. Please choose a living enemy.\n";
        }else{
            break;
        }
    }

    selectedTarget = monsters[targetChoice];

    cout << "\n" << this->getName() << " used [" << selectedSkill.getName() << "]!\n";
    
    selectedSkill.use(monsters, this, selectedTarget);
}

void Player::applyGearStats(const Item& gear, bool isEquipping){
    if(gear.isEmpty()){
        return;
    }

    Effect effect = gear.getEffect();
    int modifier = isEquipping ? 1 : -1;
    int finalValue = effect.getValue() * modifier;

    if(effect.getType() == ValueType::Flat){
        this->addBonusFlat(effect.getTag(), finalValue);
    }else{
        this->addBonusPercent(effect.getTag(), finalValue);
    }

    if(!isEquipping){
        setHp(getHp()); 
        setMp(getMp());
    }
}

void Player::changeEquipment(size_t index){
    Item targetGear = backpack.getItem(index);
    
    if(targetGear.getType() == "Weapon"){
        if(!equippedWeapon.isEmpty()){
            applyGearStats(equippedWeapon, false);
            backpack.addItem(equippedWeapon);
        }
        
        equippedWeapon = targetGear;
        equippedWeapon.setQuantity(1);
        backpack.removeItem(index);
        applyGearStats(equippedWeapon, true);
    }else if(targetGear.getType() == "Equipment"){
        if(!equippedArmor.isEmpty()){
            applyGearStats(equippedArmor, false);
            backpack.addItem(equippedArmor);
        }
        
        equippedArmor = targetGear;
        equippedArmor.setQuantity(1);
        backpack.removeItem(index);
        applyGearStats(equippedArmor, true);
    }
}

PlayerSkill::PlayerSkill(): Skill(){}
PlayerSkill::PlayerSkill(string theName, Target theTarget, vector<Effect> theEffect, int theDamageMultiplier, int theMpCost):
    Skill(theName, theDamageMultiplier, theMpCost){}

void PlayerSkill::addEffect(const Effect& theEffect, Target theTarget){
    effects.push_back(theEffect);
}

void PlayerSkill::use(vector<Creature*> monsters, Creature* caster, Creature* theTarget) const{
    vector<Creature*> validTargets;

    if(skillTarget == Target::All){
        for(auto* monster : monsters){
            if(monster != nullptr && monster->isAlive()){
                validTargets.push_back(monster);
            }
        }
    }else{
        if(theTarget != nullptr && theTarget->isAlive()){
            validTargets.push_back(theTarget);
        }else{
            cout << "無效的目標！" << endl;
            return; 
        }
    }
    
    for(auto* target : validTargets){
        if(getDamage() > 0){
            int finalDamage = caster->getAtk() * getDamage();
            caster->attack(*target, finalDamage);
        }
        for(const auto& effect : effects){
            effect.execute(*target);
        }
    }
}

PlayerSkill& PlayerSkill::attach(const Effect& theEffect, Target theTarget){
    effects.push_back(theEffect);
    return *this;
}

Swordman::Swordman(): Player(){}
Swordman::Swordman(string theName): Player(theName, 160, 30,  8,  16, 2,  12, 6,  10, 6){}
Swordman::Swordman(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

SwordMaster::SwordMaster(): Swordman(){}
SwordMaster::SwordMaster(string theName): Swordman(theName, 280, 60, 16, 30, 4, 16, 10, 16, 10){}
SwordMaster::SwordMaster(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Swordman(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Warrior::Warrior(): Player(){}
Warrior::Warrior(string theName): Player(theName, 200, 20, 6, 12, 2, 18, 4, 8, 5){}
Warrior::Warrior(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Crusader::Crusader(): Warrior(){}
Crusader::Crusader(string theName): Warrior(theName,350,80,8,18,8,32,18,12,8){}
Crusader::Crusader(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Warrior(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Wizard::Wizard(): Player(){}
Wizard::Wizard(string theName): Player(theName, 80, 150, 8, 3, 18, 4, 14, 8, 5){}
Wizard::Wizard(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

ArchWizard::ArchWizard(): Wizard(){}
ArchWizard::ArchWizard(string theName): Wizard(theName, 140, 300, 12, 5, 35, 6, 24, 12, 8){}
ArchWizard::ArchWizard(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Wizard(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Priest::Priest(): Player(){}
Priest::Priest(string theName): Player(theName, 100, 120, 8, 6, 12, 8, 12, 10, 8){}
Priest::Priest(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

ArchPriest::ArchPriest(): Priest(){}
ArchPriest::ArchPriest(string theName): Priest(theName, 180, 240, 12, 10, 22, 12, 20, 15, 12){}
ArchPriest::ArchPriest(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Priest(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Archer::Archer(): Player(){}
Archer::Archer(string theName): Player(theName, 110, 50, 11, 11, 4, 6, 6, 18, 8){}
Archer::Archer(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Thief::Thief(): Player(){}
Thief::Thief(string theName): Player(theName, 90, 40, 18, 13, 2, 5, 5, 10, 12){}
Thief::Thief(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Assassin::Assassin(): Thief(){}
Assassin::Assassin(string theName): Thief(theName, 160, 70, 30, 24, 4, 9, 8, 14, 22){}
Assassin::Assassin(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Thief(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}