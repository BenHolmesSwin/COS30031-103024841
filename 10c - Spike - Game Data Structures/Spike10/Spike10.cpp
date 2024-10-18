// Spike10.cpp

#include <iostream>
#include <vector>

using namespace std;

enum ItemType {
    Sword,
    Rock,
    Bag,
    Potion,
    Rope,
};

class Item {
public:
    Item(int inId, ItemType inType, string desc) {
        id = inId;
        type = inType;
        description = desc;
    }
    int id;
    ItemType type;
    string description;
};

class Player {
public:
    Player(int inHealth) {
        health = inHealth;
    }
    vector<Item> inventory;
    int health;
    void addItem(Item item) {
        inventory.push_back(item);
    }
    void removeItem(int id) {
        inventory.erase(inventory.begin() + id);
    }
};

int main()
{
    //player creation and inventory
}
