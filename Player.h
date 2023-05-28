#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Room.h"

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

    // Action towards item
    void addItem(Item* item);
    void removeItem(const std::string& itemName);
    bool hasItem(const std::string& itemName) const;
    Item* getItem(const std::string& itemName) const;
    void showInventory() const;
    void addDroppedItem(Item* item);

    // Action towards character
    void attack(Character* target);
    void increaseHealth(int amount);
    void decreaseHealth(int amount);
    int getHealth() const;
    void showHealth() const;

    void setCurrentWeapon(Item* item);
    Item* getCurrentWeapon() const;

    void setScore(int num);
    int getScore() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<Item*> inventory;
    int health;
    Item* currentWeapon;
    int score = 0;
    std::vector<Item*> droppedItems;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you.", 100, 0),
               currentRoom(new NullRoom()), health(100) {}
};


#endif //ZOORK_PLAYER_H
