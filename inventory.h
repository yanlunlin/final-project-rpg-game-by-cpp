#include<vector>
#include"item.h"

using std::vector;

class Inventory{
    private:
        size_t size;
        vector<Item> storage;
    public:
        Inventory();
        Inventory(size_t theSize, const vector<Item>& theStorage);

        size_t getSize() const;
        const vector<Item>& getStorage() const;

        void setSize(size_t theSize);
        void setStorage(const vector<Item>& theStorage);

        void useItem(size_t index);
};