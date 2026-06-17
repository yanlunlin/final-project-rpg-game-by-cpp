#include "Item.h"
#include <iostream>

Item::Item(std::string itemName, std::string itemType, int value, int qty) {
    name = itemName;
    type = itemType;
    effectValue = value;
    quantity = qty;
}

std::string Item::getName() {
    return name;
}

std::string Item::getType() {
    return type;
}

int Item::getEffectValue() {
    return effectValue;
}

int Item::getQuantity() {
    return quantity;
}

void Item::setQuantity(int qty) {
    if (qty >= 0) {
        quantity = qty;
    } else {
        quantity = 0;
    }
}

bool Item::isAvailable() {
    return quantity > 0;
}

bool Item::use() {
    if (isAvailable()) {
        quantity--;
        return true;
    }
    return false;
}

void Item::showInfo() {
    std::cout << "[" << type << "] " << name 
              << " (Effect: " << effectValue 
              << ") - Quantity: " << quantity << std::endl;
}