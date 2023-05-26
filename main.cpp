#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"


int main() {
    // TO DO: Create 10 rooms
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                           "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                    "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                  "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> north_of_house = std::make_shared<Room>("north-of-house", "You are facing the north side of a white house.\n");
    std::shared_ptr<Room> west_of_house = std::make_shared<Room>("west-of-house", "You are facing the west side of a white house.\n");


    // Relation between the room
    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", false);
    Passage::createBasicPassage(start.get(), north_of_house.get(), "north", false);
    Passage::createBasicPassage(start.get(), west_of_house.get(), "west", false);

    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);
    Passage::createBasicPassage(south_of_house.get(), west_of_house.get(), "west", true);

    Passage::createBasicPassage(west_of_house.get(), north_of_house.get(), "north", true);

    Passage::createBasicPassage(north_of_house.get(), west_of_house.get(), "west", true);
    Passage::createBasicPassage(north_of_house.get(), behind_house.get(), "south", true);


    // Create items
    Item* sword = new Item("sword", "A sharp sword");
    north_of_house->addItem(sword);

    // Create character
    Character* troll = new Character("troll", "A huge troll", 150);
    south_of_house->addCharacter(troll);




    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
