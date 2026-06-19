#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    std::string type;
    int effectValue;
    int quantity;

public:
    Item(std::string itemName, std::string itemType, int value, int qty);

    std::string getName();
    std::string getType();
    int getEffectValue();
    int getQuantity();
    void setQuantity(int qty);
    bool isAvailable();
    bool use();
    void showInfo() const;
};

#endif