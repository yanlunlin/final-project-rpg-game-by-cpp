#include "item.h"
#include <iostream>

Item::Item(std::string itemName, std::string itemType, Effect itemEffect, int qty): name(itemName), type(itemType), effect(itemEffect), quantity(qty){}

std::string Item::getName() const{
    return name;
}

std::string Item::getType() const{
    return type;
}

Effect Item::getEffect() const{
    return effect;
}

int Item::getQuantity() const{
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

bool Item::isEmpty() const{
    return name.empty() || type == "None";
}

bool Item::use() {
    if (isAvailable()) {
        quantity--;
        return true;
    }
    return false;
}

void Item::showInfo() const {
    std::cout << "[" << type << "] " << name 
              << " (Effect: " << effect.getName() 
              << ") - Quantity: " << quantity << std::endl;
}

Item Item::CreateEmpty(){ 
    return Item("", "None", Effect("", "", ValueType::Flat, 0, 0), 0); 
}