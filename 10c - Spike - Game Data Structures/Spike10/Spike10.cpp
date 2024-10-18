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
            cout << endl;
        }
        cout << "=============" << endl;
    }
};

int main()
{
    //player creation and inventory
    Player player = Player(100);
    player.addItem(Item(0, Sword, "A basic sword"));
    player.addItem(Item(1, Sword, "A basic sword"));
    player.addItem(Item(2, Rock, "A small rock"));
    player.addItem(Item(3, Bag, "A bag that can store something"));

    //viewing
    cout << "Viewing the inverntory!" << endl;
    player.showInventory();

    //adding item
    cout << "Adding a Rope" << endl;
    player.addItem(Item(4, Rope, "A rope you can use to climb"));
    player.showInventory();

    //deleting item
    cout << "deleteing a sword (item id 1)" << endl;
    player.removeItem(1);//index
    player.showInventory();

}
