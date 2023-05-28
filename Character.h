#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>

class Player;
class Character : public GameObject {
public:
    Character(const std::string &, const std::string &, const int &, const int &);
    virtual ~Character();
    void talk() const;
    void decreaseHealth(int amount);
    int getHealth() const;
    int getAttackDamage() const;
    void counterAttack(Player* player, int damage);

protected:
    int health;
    int attackDamage;
};

#endif //ZOORK_CHARACTER_H
