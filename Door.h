#include "Passage.h"
#include "Item.h"
#include "Character.h"


class Door : public Passage {
public:
    Door(Room* from, Room* to, const std::string& direction, const std::string& description, Item* requiredKey);

    virtual std::string getDescription() const;
    virtual Item* getRequiredKey() const;
    void setOpenState(bool open) {
        openState = open;
    }
    bool isDoorOpen() const;
    std::string getDirection() const;
private:
    std::string description;
    Item* requiredKey;
    bool openState;
    std::string direction;
};

