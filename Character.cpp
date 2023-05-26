#include "Character.h"
#include "Player.h"

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
void Character::counterAttack(Player* player, int damage) {
    // Check if the player is null or already defeated
    if (!player || player->getHealth() <= 0) {
        return;
    }

    // Perform the counterattack
    std::cout << getName() << " counterattacks you by " << damage << " HP!\n";
    player->decreaseHealth(damage);

    // Check if the player is defeated
    if (player->getHealth() <= 0) {
        std::cout << "You have been defeated!\n";
    } else {
        std::cout <<  "You have " << player->getHealth() << " HP remaining.\n";
    }
}





