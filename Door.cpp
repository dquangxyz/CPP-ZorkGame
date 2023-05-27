#include "Door.h"
#include "Player.h"
#include "Character.h"

Door::Door(Room* from, Room* to, const std::string& direction, const std::string& description, Item* requiredKey)
        : Passage(direction, description, from, to), requiredKey(requiredKey), direction(direction) {}

std::string Door::getDescription() const {
    std::string descriptionText = Passage::getDescription();
    if (requiredKey) {
        descriptionText += " It requires a " + requiredKey->getName() + " to open.";
    }
    return descriptionText;
}

Item* Door::getRequiredKey() const {
    return requiredKey;
}
bool Door::isDoorOpen() const {
    return openState;
}
std::string Door::getDirection() const {
    return direction;
}
