#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(Item* item) {
    // Check if the item has been dropped before
    if (std::find(droppedItems.begin(), droppedItems.end(), item) != droppedItems.end()) {
        inventory.push_back(item);
        return;
    }
    inventory.push_back(item);

   if (item->getTag() == "drink"){
       score += 15;
   } else if (item->getTag() == "weapon"){
       score += 10;
   } else {
       score += 5;
   }
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

void Player::addDroppedItem(Item* item) {
    droppedItems.push_back(item);
}


void Player::attack(Character* target) {
    int damage = 0;

    if (currentWeapon && currentWeapon->getName() == "sword") {
        damage = 50;
    } else if (currentWeapon && currentWeapon->getName() == "spear") {
        damage = 40;
    } else if (currentWeapon && currentWeapon->getName() == "axe") {
        damage = 30;
    } else {
        std::cout << "You don't have a weapon to attack. Equip and use your weapon if you have.\n";
        return;
    }

    target->decreaseHealth(damage);
    std::cout << "You attack " << target->getName() << " with " << damage << " damage!\n";

    if (target->getHealth() <= 0) {
        std::cout << target->getName() << " has been defeated!\n";
        score += 50;
        Room* currentRoom = getCurrentRoom();
        currentRoom->removeCharacter(target);
    } else {
        std::cout << target->getName() << " has " << target->getHealth() << " HP left.\n";
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
void Player::increaseHealth(int amount) {
    health += amount;
}
void Player::showHealth() const {
    std::cout << "Your current health: " << health << " HP\n";
}
void Player::setCurrentWeapon(Item* item) {
    currentWeapon = item;
}
Item* Player::getCurrentWeapon() const {
    return currentWeapon;
}
void Player::setScore(int num) {
    score = num;
}
int Player::getScore() const {
    return score;
}
