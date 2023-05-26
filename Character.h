//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>

class Player;
class Character : public GameObject {
public:
    Character(const std::string &, const std::string &, const int &);
    void talk() const;
    void decreaseHealth(int amount);
    int getHealth() const;
    void counterAttack(Player* player, int damage);

protected:
//    std::vector<Item*> inventory;
//    std::vector<std::string> tags;
    int health;
//    int attack;
//    int move;
//    int initiative;
};

#endif //ZOORK_CHARACTER_H
