//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "NullRoom.h"
#include "Room.h"
#include <iostream>

class Passage : public Location {
public:
    static void createBasicPassage(Room* from, Room* to, const std::string& direction, bool bidirectional = true);

    Passage(const std::string& name, const std::string& description, Room* from, Room* to);

    Passage(const std::string& name, const std::string& description, std::shared_ptr<Command> enterCommand, Room* from, Room* to);

    void setFrom(Room* from);
    Room* getFrom() const;

    void setTo(Room* to);
    Room* getTo() const;


protected:
    static std::string oppositeDirection(const std::string& direction);

    Room* fromRoom;
    Room* toRoom;
};


#endif //ZOORK_PASSAGE_H
