#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Door.h"


int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                                                  "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                                                "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> north_of_house = std::make_shared<Room>("north-of-house", "You are facing the north side of a white house.\n");
    std::shared_ptr<Room> west_of_house = std::make_shared<Room>("west-of-house", "You are facing the west side of a white house.\n");
    std::shared_ptr<Room> kitchen = std::make_shared<Room>("kitchen", "You are in the kitchen.\n");



    // Relation between the rooms
    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", false);
    Passage::createBasicPassage(start.get(), north_of_house.get(), "north", false);
    Passage::createBasicPassage(start.get(), west_of_house.get(), "west", false);

    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", false);
    Passage::createBasicPassage(south_of_house.get(), west_of_house.get(), "west", true);

    Passage::createBasicPassage(west_of_house.get(), north_of_house.get(), "north", false);

    Passage::createBasicPassage(north_of_house.get(), west_of_house.get(), "west", false);
    Passage::createBasicPassage(north_of_house.get(), behind_house.get(), "south", true);

    Passage::createBasicPassage(behind_house.get(), kitchen.get(), "west", true);

    // Create items
    Item* sword = new Item("sword", "A sharp sword");
    north_of_house->addItem(sword);

    Item* redKey = new Item("red key", "Key to open red doors");
    west_of_house->addItem(redKey);

    Item* greenKey = new Item("green key", "Key to open green doors");
    behind_house->addItem(greenKey);

    // Create character
    Character* troll = new Character("troll", "A huge troll", 150);
    south_of_house->addCharacter(troll);

    // Create door
    Door* door1 = new Door(west_of_house.get(), north_of_house.get(), "north", "A locked wooden door.", redKey);
    std::shared_ptr<Door> sharedDoor1(door1);
    west_of_house->addPassage("north", sharedDoor1);

    Door* door2 = new Door(behind_house.get(), kitchen.get(), "west", "A locked wooden door.", greenKey);
    std::shared_ptr<Door> sharedDoor2(door2);
    behind_house->addPassage("west", sharedDoor2);



    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
