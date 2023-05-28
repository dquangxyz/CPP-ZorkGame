#include "Character.h"
#include "Player.h"

Character::Character(const std::string &n, const std::string &d, const int &health, const int &attackDamage)
    : GameObject(n, d), health(health), attackDamage(attackDamage) {};
Character::~Character() {};


void Character::talk() const {
    if (getName() == "troll") {
        std::cout << getName() << ": You dare to approach me? Prepare to be crushed!\n";
    } else if (getName() == "joker") {
        std::cout << getName() << ": Why so serious? Let's have some fun!\n";
    } else if (getName() == "kingkong") {
        std::cout << getName() << " Gruhhhhhh \n";
    } else if ((getName() == "clawn")) {
        std::cout << getName() << ": Hello there! What's your name?\n";
        std::string playerName;
        std::getline(std::cin, playerName);

        std::cout << getName() << ": Nice to meet you, " << playerName << "! How old are you?\n";
        std::string playerAge;
        std::getline(std::cin, playerAge);

        std::cout << getName() << ": Awesome!\n";
    }
}

int Character::getHealth() const {
    return health;
}
int Character::getAttackDamage() const {
    return attackDamage;
}
void Character::decreaseHealth(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}
void Character::counterAttack(Player* player, int damage) {
    if (!player || player->getHealth() <= 0) {
        return;
    }

    std::cout << getName() << " counterattacks you by " << damage << " HP!\n";
    player->decreaseHealth(damage);
    player->showHealth();
    if (player->getHealth() <= 0) {
        std::cout << "You have been defeated!\n";
        std::cout << "Game over!\n";
        std::cout << "Your final score is " << player->getScore() << '\n';
    }
}





