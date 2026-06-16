#include"inventory.h"
#include"item.h"

using std::vector;

Inventory::Inventory(): maxSize(0){}
Inventory::Inventory(size_t theSize, const vector<Item>& theStorage): maxSize(theSize){
    if(theStorage.size() <= maxSize){
        storage = theStorage;
    }
}

size_t Inventory::getMaxSize() const{
    return maxSize;
}

const vector<Item>& Inventory::getStorage() const{
    return storage;
}

void Inventory::setMaxSize(size_t theSize){
    maxSize = theSize;
}

void Inventory::setStorage(const vector<Item>& theStorage){
    if(theStorage.size() <= maxSize){
        storage = theStorage;
    }
}

void Inventory::useItem(size_t index){
    storage[index].use();
}