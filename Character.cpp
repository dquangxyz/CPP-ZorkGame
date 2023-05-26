#include "Character.h"

Character::Character(const std::string &n, const std::string &d, const int &health) : GameObject(n, d), health(health) {};

void Character::talk() const {
    std::cout << getName() << ": Hello there! How can I assist you?\n";

    // Ask the player a question
    std::cout << getName() << ": What's your name? \n";
    std::string playerName;
    std::getline(std::cin, playerName);

    std::cout << getName() << ": Nice to meet you, " << playerName << "! How old are you? \n";
    std::string playerAge;
    std::getline(std::cin, playerAge);

    std::cout << getName() << ": Awesome! \n";
}

int Character::getHealth() const {
    return health;
}
void Character::decreaseHealth(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}





