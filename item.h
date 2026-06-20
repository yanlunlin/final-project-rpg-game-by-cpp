#ifndef ITEM_H
#define ITEM_H

#include<string>
#include"effect.h"

using std::string;

class Item {
private:
    string name;
    string type;
    Effect effect;
    int quantity;

public:
    Item(string itemName, string itemType, Effect itemEffect, int qty);

    static Item CreateEmpty();

    string getName() const;
    string getType() const;
    Effect getEffect() const;
    int getQuantity() const;
    void setQuantity(int qty);
    bool isAvailable();
    bool isEmpty() const;
    bool use();
    void showInfo() const;
};

#endif