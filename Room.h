//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);
    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    std::string getName() const;

    // For item
    std::vector<Item*> items;
    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);

    // For passage
    void addPassage(const std::string &, std::shared_ptr<Passage>);
    void removePassage(const std::string &);
    std::shared_ptr<Passage> getPassage(const std::string &);

    // For character
    std::vector<Character*> characters;
    void addCharacter(Character* character);
    void removeCharacter(Character* character);
    Character* getCharacter(const std::string& characterName);

    std::string getDoorDirection() const;

    bool hasPassage(const std::string& direction) const;

protected:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::string name;
};



#endif //ZOORK_ROOM_H
