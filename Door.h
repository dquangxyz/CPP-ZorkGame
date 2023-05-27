#include "Passage.h"
#include "Item.h"
#include "Character.h"


class Door : public Passage {
public:
    Door(Room* from, Room* to, const std::string& direction, const std::string& description, Item* requiredKey);

    virtual std::string getDescription() const;
    virtual Item* getRequiredKey() const;

private:
    std::string description;
    Item* requiredKey;
};

