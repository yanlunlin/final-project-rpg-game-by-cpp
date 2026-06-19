#include "item.h"
#include <iostream>

item::item(std::string itemName, std::string itemType, int value, int qty) {
    name = itemName;
    type = itemType;
    effectValue = value;
    quantity = qty;
}

std::string item::getName() {
    return name;
}

std::string item::getType() {
    return type;
}

int item::getEffectValue() {
    return effectValue;
}

int item::getQuantity() {
    return quantity;
}

void item::setQuantity(int qty) {
    if (qty >= 0) {
        quantity = qty;
    } else {
        quantity = 0;
    }
}

bool item::isAvailable() {
    return quantity > 0;
}

bool item::use() {
    if (isAvailable()) {
        quantity--;
        return true;
    }
    return false;
}

void item::showInfo() {
    std::cout << "[" << type << "] " << name 
              << " (Effect: " << effectValue 
              << ") - Quantity: " << quantity << std::endl;
}