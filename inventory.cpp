#include"inventory.h"
#include"item.h"

using std::vector;

Inventory::Inventory(){}
Inventory::Inventory(size_t theSize, const vector<Item>& theStorage){}

const vector<Item>& Inventory::getStorage() const{
    return storage;
}

void Inventory::useItem(size_t index){
    storage[index].use();
}