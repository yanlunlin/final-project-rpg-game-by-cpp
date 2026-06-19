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
        Inventory(size_t theSize, const vector<Item>& theStorage);

        size_t getMaxSize() const;
        const vector<Item>& getStorage() const;

        void setMaxSize(size_t theSize);
        void setStorage(const vector<Item>& theStorage);

        void useItem(size_t index);
};

#endif