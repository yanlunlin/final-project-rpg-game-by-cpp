#include<iostream>
#include"inventory.h"
#include"item.h"

using std::vector;
using std::cout;
using std::endl;

Inventory::Inventory(): maxSize(0){}
Inventory::Inventory(size_t theSize): maxSize(theSize){}
Inventory::Inventory(size_t theSize, const vector<Item>& theStorage): maxSize(theSize){
    if(theStorage.size() <= maxSize){
        storage = theStorage;
    }
}

size_t Inventory::getMaxSize() const{
    return maxSize;
}

size_t Inventory::getSize() const{
    return storage.size();
}

const vector<Item>& Inventory::getStorage() const{
    return storage;
}

const Item& Inventory::getItem(size_t index) const{
    return storage.at(index);
}

void Inventory::setMaxSize(size_t theSize){
    maxSize = theSize;
}

void Inventory::setStorage(const vector<Item>& theStorage){
    if(theStorage.size() <= maxSize){
        storage = theStorage;
    }
}

void Inventory::addItem(const Item& theItem){
    if(theItem.isEmpty()){
        return;
    }

    int incomingQty = theItem.getQuantity();

    for(auto& slot : storage){
        if(slot.getName() == theItem.getName()){
            slot.setQuantity(slot.getQuantity() + incomingQty);
            return;
        }
    }

    Item copy = theItem;
    copy.setQuantity(incomingQty);
    storage.push_back(copy);
}

void Inventory::removeItem(size_t index){
    if(index >= storage.size()){
        return;
    }
    
    int qty = storage[index].getQuantity();
    if(qty > 1){
        storage[index].setQuantity(qty - 1);
    }else{
        storage.erase(storage.begin() + index);
    }
}

Item* Inventory::usePotion(size_t index){
    if(index >= storage.size() || storage[index].getQuantity() == 0){
        return nullptr;
    }

    if(storage[index].use()){
        return &storage[index];
    }
    
    return nullptr; 
}

/*Item* Inventory::useItem(size_t index){
    if(index >= storage.size()){
        return nullptr;
    }

    if(!storage[index].use()){
        cout << storage[index].getName() << " 已經沒有剩餘數量了！" << endl;
        return nullptr;
    }

    return &storage[index];
}*/