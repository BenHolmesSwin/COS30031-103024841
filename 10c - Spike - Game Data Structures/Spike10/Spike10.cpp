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
    void addItem(Item item) {//adds item
        inventory.push_back(item);
    }
    void removeItem(int index) {//removes item via index
        inventory.erase(inventory.begin() + index);
    }
    void showInventory() {//prints entire inventory
        cout << "==Inventory==" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            cout << "Inventory Id: " << i << " |";
            cout << "Item id: " << inventory[i].id << " |";
            cout << "Item type: " << inventory[i].type << " |";
            cout << inventory[i].description << " |";
    }
};

int main()
{
    //player creation and inventory
    cout << "Adding a Rope" << endl;
    player.addItem(Item(4, Rope, "A rope you can use to climb"));
    player.showInventory();

    //deleting item
    cout << "deleteing a sword (item id 1)" << endl;
    player.removeItem(1);//index
    player.showInventory();

}
