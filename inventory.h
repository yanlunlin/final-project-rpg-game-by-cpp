#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"

using std::vector;

class Inventory{
    private:
        size_t maxSize;
        vector<Item> storage;
    public:
        Inventory();
        Inventory(size_t theSize);
        Inventory(size_t theSize, const vector<Item>& theStorage);

        size_t getMaxSize() const;
        size_t getSize() const;
        const vector<Item>& getStorage() const;
        const Item& getItem(size_t index) const;

        void setMaxSize(size_t theSize);
        void setStorage(const vector<Item>& theStorage);

        void addItem(const Item& theItem);
        void removeItem(size_t index);
        Item* usePotion(size_t index);
        /*Item* useItem(size_t index);*/
};

#endif