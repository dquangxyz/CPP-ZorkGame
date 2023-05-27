//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"
#include "Door.h"

#include <utility>


Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

// Method related to Passage
void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}
void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}
std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

// Method related to Item
void Room::addItem(Item *item) {
    items.push_back(item);
}
Item* Room::getItem(const std::string& itemName) {
    for (Item* item : items) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}
void Room::removeItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == itemName) {
            items.erase(it);
            std::cout << "You have removed the " << itemName << " from the room.\n";
            return;
        }
    }
}

// Method related to Character
void Room::addCharacter(Character* character) {
    characters.push_back(character);
}
void Room::removeCharacter(Character* character) {
    auto it = std::find(characters.begin(), characters.end(), character);
    if (it != characters.end()) {
        characters.erase(it);
    }
}
Character* Room::getCharacter(const std::string& characterName) {
    for (Character* character : characters) {
        if (character->getName() == characterName) {
            return character;
        }
    }
    return nullptr;
}

bool Room::hasPassage(const std::string& direction) const {
    // Check if a passage exists in the specified direction
    return (passageMap.find(direction) != passageMap.end());
}

std::string Room::getDoorDirection() const {
    for (const auto& passagePair : passageMap) {
        if (std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(passagePair.second)) {
            return door->getDirection();
        }
    }
    return "unknown";
}










