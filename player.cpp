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
): Creature(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk), backpack(20){
    skillBook = {
        PlayerSkill("普通攻擊", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, {}, 1, 0)
    };
}

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

    theEffect.execute(*this);

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
            cout << name << " 喝下了 [" << potionPtr->getName() << "]！" << endl;
            this->addActiveEffect(potionPtr->getEffect());
        }
        
        if(backpack.getItem(index).getQuantity() == 0){
            backpack.removeItem(index);
        }
    }else if(itemType == "Weapon" || itemType == "Equipment"){
        this->changeEquipment(index);
    }
}

void Player::addItem(const Item& theItem){
    backpack.addItem(theItem);
}

void Player::action(vector<Creature*> team, vector<Creature*> monsters){
    if(!this->isAlive()){
        return;
    }

    cout << "\n====================================\n";
    cout << "輪到" << this->getName() << "行動!\n";
    cout << "====================================";

    updateEffects();

    int actionChoice = -1;

    do{
        while(true){
            cout << "\n請選擇行動:\n";
            cout << "[0] 使用道具\n";
            cout << "[1] 使用技能\n";
            cout << "輸入行動編號: ";
            cin >> actionChoice;

            if(cin.fail() || actionChoice < 0 || actionChoice > 1){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "輸入錯誤, 請再次嘗試\n";
            }else{
                break;
            }
        }
        
        if(actionChoice == 0){
            vector<Item> itemList = this->getItemList();
            if(itemList.empty()){
                cout << "這裡空空如也\n";
            }else{
                cout << "\n選擇使用道具:\n";
                for(size_t i = 0; i < itemList.size(); i++){
                    cout << "[" << i << "] " << itemList[i].getName() << "(*" << itemList[i].getQuantity() << ")" << endl;
                }

                int itemChoice = -1;

                while(true){
                    cout << "輸入道具編號: ";
                    cin >> itemChoice;

                    if(cin.fail() || itemChoice < 0 || itemChoice >= itemList.size()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "輸入錯誤, 請再次嘗試\n";
                    }else{
                        break;
                    }
                }

                useItem(itemChoice);
            }
        }
    }while(actionChoice == 0);
    
    if(skillBook.empty()){
        cout << this->getName() << "不會任何技能, 只能發呆...\n";
        return;
    }

    cout << "\n選擇並使用技能:\n";
    for(size_t i = 0; i < skillBook.size(); ++i){
        cout << "[" << i << "] ";
        skillBook[i].showInfo();
    }

    int skillChoice = -1;

    while(true){
        cout << "請輸入技能編號: ";
        cin >> skillChoice;

        if(cin.fail() || skillChoice < 0 || skillChoice >= skillBook.size()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "輸入錯誤, 請再次嘗試\n";
        }else{
            break;
        }
    }

    PlayerSkill& selectedSkill = skillBook[skillChoice];

    Creature* selectedTarget = nullptr;
    vector<Creature*>& targetList = (selectedSkill.getTargetType() == PlayerSkill::TargetType::AllEnemies || selectedSkill.getTargetType() == PlayerSkill::TargetType::SingleEnemy) ? monsters : team;

    cout << "\n選擇使用對象:\n";
    if(selectedSkill.getTargetType() == PlayerSkill::TargetType::AllEnemies || selectedSkill.getTargetType() == PlayerSkill::TargetType::SingleEnemy){
        for(size_t i = 0; i < monsters.size(); ++i){
            if(monsters[i] != nullptr && monsters[i]->isAlive()){
                cout << "[" << i << "] " << monsters[i]->getName() << " (HP: " << monsters[i]->getHp() << "/" << monsters[i]->getMaxHp() << ")\n";
            }
        }
    }else if(selectedSkill.getTargetType() == PlayerSkill::TargetType::AllAllies || selectedSkill.getTargetType() == PlayerSkill::TargetType::SingleAlly){
        for(size_t i = 0; i < team.size(); ++i){
            if(team[i] != nullptr && team[i]->isAlive()){
                cout << "[" << i << "] " << team[i]->getName() << " (HP: " << team[i]->getHp() << "/" << team[i]->getMaxHp() << ")\n";
            }
        }
    }


    int targetChoice = -1;
    while(true){
        cout << "輸入使用對象編號: ";
        cin >> targetChoice;

        if(cin.fail() || targetChoice < 0 || targetChoice >= targetList.size() || targetList[targetChoice] == nullptr || !targetList[targetChoice]->isAlive()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "輸入錯誤, 請再次嘗試\n";
        }else{
            break;
        }
    }

    selectedTarget = targetList[targetChoice];

    cout << "\n" << this->getName() << " 使出了 [" << selectedSkill.getName() << "]!\n";
    
    selectedSkill.use(monsters, team, this, selectedTarget);
}

void Player::showInfo() const{
    cout << getName() << "\t| ";
    cout << "Hp: " << getHp() << "/" << getMaxHp() << "\t| ";
    cout << "Mp: " << getMp() << "/" << getMaxMp() << endl;
}

void Player::showDetailInfo() const{
    cout << getName() << ":\n";
    cout << "Hp: " << getHp() << "/" << getMaxHp() << "\n";
    cout << "Mp: " << getMp() << "/" << getMaxMp() << "\n";
    cout << "Atk: " << getAtk() << " | " << "Matk: " << getMatk() << "\n";
    cout << "Def: " << getDef() << " | " << "Mdef: " << getMdef() << "\n";
    cout << "Agi: " << getAgi() << " | " << "Dex: " << getDex() << " | " << "Luk: " << getLuk() << endl;
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
PlayerSkill::PlayerSkill(string theName, TargetType theTgtType, DamageType theDmgType, vector<Effect> theEffects, int theDamageMultiplier, int theMpCost
): Skill(theName, theDamageMultiplier, theMpCost), skillTarget(theTgtType), dmgType(theDmgType), effects(theEffects){}

PlayerSkill::TargetType PlayerSkill::getTargetType() const{
    return skillTarget;
}

PlayerSkill::DamageType PlayerSkill::getDamageType() const{
    return dmgType;
}

void PlayerSkill::setTargetType(TargetType theTgtType){
    skillTarget = theTgtType;
}

void PlayerSkill::setDamageType(DamageType theDmgType){
    dmgType = theDmgType;
}

void PlayerSkill::use(vector<Creature*> enemies, vector<Creature*> allies, Creature* caster, Creature* theTarget) const{
    vector<Creature*> validTargets;

    if(skillTarget == TargetType::AllEnemies){
        for(auto* enemy : enemies){
            if(enemy != nullptr && enemy->isAlive()){
                validTargets.push_back(enemy);
            }
        }
    }else if(skillTarget == TargetType::AllAllies){
        for(auto* ally : allies){
            if(ally != nullptr && ally->isAlive()){
                validTargets.push_back(ally);
            }
        }
    }else if(skillTarget == TargetType::SingleEnemy || skillTarget == TargetType::SingleAlly){
        if(theTarget != nullptr && theTarget->isAlive()){
            validTargets.push_back(theTarget);
        }else{
            cout << "無效的目標！" << endl;
            return; 
        }
    }
    
    for(auto* target : validTargets){
        if(getDamage() > 0){
            if(dmgType == DamageType::Physical){
                int finalDamage = caster->getAtk() * getDamage();
                caster->attack(*target, finalDamage);
            }else if(dmgType == DamageType::Magical){
                int finalDamage = caster->getMatk() * getDamage(); 
                caster->magicAttack(*target, finalDamage);
            }
        }
        for(const auto& effect : effects){
            effect.execute(*target);
            target->addActiveEffect(effect);
        }
    }
}

void PlayerSkill::showInfo() const{
    cout << getName() << "\t| 消耗Mp: " << getMpCost() << "\n";
}

void PlayerSkill::addEffect(const Effect& theEffect, TargetType theTarget){
    effects.push_back(theEffect);
}

PlayerSkill& PlayerSkill::attach(const Effect& theEffect, TargetType theTarget){
    effects.push_back(theEffect);
    return *this;
}

Swordman::Swordman(): Player(){}
Swordman::Swordman(string theName): Player(theName, 160, 30,  8,  16, 2,  12, 6,  10, 6){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("破甲重擊", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("破甲", "def", ValueType::Percent, -30, 2)}, 2, 15),
        PlayerSkill("旋風斬", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Physical, 
        {Effect("流血", "hp", ValueType::Flat, -20, 3)}, 1, 25)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());
}
Swordman::Swordman(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

SwordMaster::SwordMaster(): Swordman(){}
SwordMaster::SwordMaster(string theName): Swordman(theName, 280, 60, 16, 30, 4, 16, 10, 16, 10){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("幻影劍舞", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("神速", "agi", ValueType::Percent, 30, 2)}, 4, 25),
        PlayerSkill("裂地劍氣", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Physical, 
        {Effect("武器破壞", "atk", ValueType::Percent, -20, 2)}, 2, 30)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
SwordMaster::SwordMaster(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Swordman(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Warrior::Warrior(): Player(){}
Warrior::Warrior(string theName): Player(theName, 200, 20, 6, 12, 2, 18, 4, 8, 5){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("無畏戰吼", PlayerSkill::TargetType::AllAllies, PlayerSkill::DamageType::Physical, 
        {Effect("防禦提升", "def", ValueType::Percent, 30, 3)}, 0, 15),
        PlayerSkill("碎骨重擊", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("攻擊下降", "atk", ValueType::Percent, -25, 2)}, 2.5, 20)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Warrior::Warrior(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Crusader::Crusader(): Warrior(){}
Crusader::Crusader(string theName): Warrior(theName, 350, 80, 8, 18, 8, 32, 18, 12, 8){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("聖盾庇護", PlayerSkill::TargetType::AllAllies, PlayerSkill::DamageType::Physical, 
        {Effect("魔法護盾", "mdef", ValueType::Percent, 40, 3)}, 0, 25),
        PlayerSkill("審判盾擊", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("暈眩遲緩", "agi", ValueType::Percent, -50, 1)}, 2, 20)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Crusader::Crusader(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Warrior(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Wizard::Wizard(): Player(){}
Wizard::Wizard(string theName): Player(theName, 80, 150, 8, 3, 18, 4, 14, 8, 5){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("隕石火雨", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Magical, 
        {Effect("燃燒", "hp", ValueType::Flat, -15, 3)}, 2, 35),
        PlayerSkill("雷擊術", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Magical, 
        {Effect("感電", "mdef", ValueType::Percent, -20, 2)}, 3, 20)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Wizard::Wizard(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

ArchWizard::ArchWizard(): Wizard(){}
ArchWizard::ArchWizard(string theName): Wizard(theName, 140, 300, 12, 5, 35, 6, 24, 12, 8){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("絕對零度", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Magical, 
        {Effect("凍結", "agi", ValueType::Percent, -40, 2)}, 3, 60),
        PlayerSkill("毀滅黑洞", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Magical, 
        {Effect("魔防崩塌", "mdef", ValueType::Percent, -50, 3)}, 5, 80)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
ArchWizard::ArchWizard(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Wizard(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Priest::Priest(): Player(){}
Priest::Priest(string theName): Player(theName, 100, 120, 8, 6, 12, 8, 12, 10, 8){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("大治癒術", PlayerSkill::TargetType::SingleAlly, PlayerSkill::DamageType::Magical, 
        {Effect("神聖治癒", "hp", ValueType::Percent, 50, 1)}, 0, 20),
        PlayerSkill("聖光領域", PlayerSkill::TargetType::AllAllies, PlayerSkill::DamageType::Magical, 
        {Effect("生命恢復", "hp", ValueType::Flat, 30, 3)}, 0, 35)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Priest::Priest(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

ArchPriest::ArchPriest(): Priest(){}
ArchPriest::ArchPriest(string theName): Priest(theName, 180, 240, 12, 10, 22, 12, 20, 15, 12){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("奇蹟之雨", PlayerSkill::TargetType::AllAllies, PlayerSkill::DamageType::Magical, 
        {Effect("群體治癒", "hp", ValueType::Percent, 40, 1)}, 0, 60),
        PlayerSkill("神聖祝福", PlayerSkill::TargetType::SingleAlly, PlayerSkill::DamageType::Magical, 
        {Effect("幸運爆發", "luk", ValueType::Percent, 50, 3)}, 0, 40)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
ArchPriest::ArchPriest(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Priest(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Archer::Archer(): Player(){}
Archer::Archer(string theName): Player(theName, 110, 50, 11, 11, 4, 6, 6, 18, 8){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("貫穿箭", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("裝甲貫穿", "def", ValueType::Percent, -20, 2)}, 2, 12),
        PlayerSkill("劇毒陷阱", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Physical, 
        {Effect("中毒", "hp", ValueType::Flat, -10, 4)}, 1, 20)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Archer::Archer(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Thief::Thief(): Player(){}
Thief::Thief(string theName): Player(theName, 90, 40, 18, 13, 2, 5, 5, 10, 12){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("疾風步", PlayerSkill::TargetType::SingleAlly, PlayerSkill::DamageType::Physical,
        {Effect("殘影", "agi", ValueType::Percent, 40, 3)}, 0, 10),
        PlayerSkill("割喉", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("大出血", "hp", ValueType::Flat, -15, 3)}, 2, 15)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Thief::Thief(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Player(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}

Assassin::Assassin(): Thief(){}
Assassin::Assassin(string theName): Thief(theName, 160, 70, 30, 24, 4, 9, 8, 14, 22){
    vector<PlayerSkill> jobSkill = {
        PlayerSkill("致命暗殺", PlayerSkill::TargetType::SingleEnemy, PlayerSkill::DamageType::Physical, 
        {Effect("弱點暴露", "def", ValueType::Percent, -30, 1)}, 4, 30),
        PlayerSkill("影襲千刃", PlayerSkill::TargetType::AllEnemies, PlayerSkill::DamageType::Physical, 
        {Effect("猛毒", "hp", ValueType::Percent, -5, 3)}, 2, 40)
    };
    skillBook.insert(skillBook.end(), jobSkill.begin(), jobSkill.end());}
Assassin::Assassin(string theName, unsigned int theHp, unsigned int theMp, unsigned int theAgi,
    unsigned int theAtk, unsigned int theMatk, unsigned int theDef, unsigned int theMdef,
    unsigned int theDex, unsigned int theLuk
): Thief(theName, theHp, theMp, theAgi, theAtk, theMatk, theDef, theMdef, theDex, theLuk){}