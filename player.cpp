#include<string>
#include"player.h"
#include"monster.h"
#include"inventory.h"

using std::string;
using std::vector;

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

/*void Player::attack(Monster& target){
    target.takeDamage(getAttackPower());
}

void Player::takeDamage(const Monster& attacker, int damage){
    setHp(hp - damage);
}*/

void Player::useItem(size_t index){
    backpack.useItem(index);
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