#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(Item* item) {
    inventory.push_back(item);
    std::cout << "You have taken the " << item->getName() << ".\n";
}

void Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            inventory.erase(it);
            std::cout << "You have dropped the " << itemName << ".\n";
            return;
        }
    }
    std::cout << "You don't have that item.\n";
}

bool Player::hasItem(const std::string& itemName) const {
    for (Item* item : inventory) {
        if (item->getName() == itemName) {
            return true;
        }
    }
    return false;
}

Item* Player::getItem(const std::string& itemName) const {
    for (Item* item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

void Player::showInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty.\n";
    } else {
        std::cout << "Your inventory:\n";
        for (const Item* item : inventory) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
}

void Player::attack(Character* target) {
    // Check if the player has a sword item
    if (!hasItem("sword")) {
        std::cout << "You don't have a sword to attack.\n";
        return;
    }
    int damage = 50;
    target->decreaseHealth(damage);
    std::cout << "You attack " << target->getName() << " with " << damage << " damage! \n";

    if (target->getHealth() <= 0) {
        std::cout << target->getName() << " has been defeated!\n";
        Room* currentRoom = getCurrentRoom();
        currentRoom->removeCharacter(target);
    } else {
        std::cout << target->getName() << " has " << target->getHealth() << " HP left \n";
    }
}
int Player::getHealth() const {
    return health;
}
void Player::decreaseHealth(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}
void Player::showHealth() const {
    std::cout << "Your current health: " << health << " HP\n";
}
