#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"
#include "Door.h"


int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room", "You are standing in an open field west of a white house, with a boarded front door.\n");
    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house", "You are facing the south side of a white house.\n");
    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house", "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");
    std::shared_ptr<Room> north_of_house = std::make_shared<Room>("north-of-house", "You are facing the north side of a white house.\n");
    std::shared_ptr<Room> west_of_house = std::make_shared<Room>("west-of-house", "You are facing the west side of a white house.\n");
    std::shared_ptr<Room> kitchen = std::make_shared<Room>("kitchen", "You are in the kitchen.\n");
    std::shared_ptr<Room> living_room = std::make_shared<Room>("living-room", "You are in the living room.\n");
    std::shared_ptr<Room> attic = std::make_shared<Room>("attic", "You are in the attic of the house.\n");
    std::shared_ptr<Room> clearing1 = std::make_shared<Room>("clearing", "You are in a clear area.\n");
    std::shared_ptr<Room> clearing2 = std::make_shared<Room>("clearing", "You are in a clear area.\n");
    std::shared_ptr<Room> forest1 = std::make_shared<Room>("forest", "You are in a forest.\n");
    std::shared_ptr<Room> forest2 = std::make_shared<Room>("forest", "You are in a forest.\n");
    std::shared_ptr<Room> canyon_view = std::make_shared<Room>("canyon-view", "You are in the Canyon View.\n");
    std::shared_ptr<Room> rocky_ledge = std::make_shared<Room>("rocky-ledge", "You are in the Rocky Ledge.\n");
    std::shared_ptr<Room> canyon_bottom = std::make_shared<Room>("canyon-bottom", "You are in the Canyon Bottom.\n");
    std::shared_ptr<Room> secret_chamber = std::make_shared<Room>("secret-chamber", "You are in the Secret Chamber.\n");

    // Relation between the rooms
    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", false);
    Passage::createBasicPassage(start.get(), north_of_house.get(), "north", false);
    Passage::createBasicPassage(start.get(), west_of_house.get(), "west", false);

    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "north", true);
    Passage::createBasicPassage(south_of_house.get(), west_of_house.get(), "west", true);
    Passage::createBasicPassage(south_of_house.get(), forest1.get(), "east", true);

    Passage::createBasicPassage(west_of_house.get(), north_of_house.get(), "north", false);

    Passage::createBasicPassage(north_of_house.get(), west_of_house.get(), "west", false);
    Passage::createBasicPassage(north_of_house.get(), behind_house.get(), "south", true);
    Passage::createBasicPassage(north_of_house.get(), secret_chamber.get(), "north", true);
    Passage::createBasicPassage(north_of_house.get(), clearing2.get(), "east", true);

    Passage::createBasicPassage(clearing2.get(), forest2.get(), "east", true);

    Passage::createBasicPassage(forest2.get(), clearing1.get(), "south", true);

    Passage::createBasicPassage(clearing1.get(), forest1.get(), "south", true);
    Passage::createBasicPassage(clearing1.get(), canyon_view.get(), "east", true);

    Passage::createBasicPassage(behind_house.get(), clearing1.get(), "east", true);
    Passage::createBasicPassage(behind_house.get(), kitchen.get(), "west", true);

    Passage::createBasicPassage(kitchen.get(), living_room.get(), "west", true);
    Passage::createBasicPassage(kitchen.get(), attic.get(), "up", true);

    Passage::createBasicPassage(canyon_view.get(), rocky_ledge.get(), "down", true);

    Passage::createBasicPassage(rocky_ledge.get(), canyon_bottom.get(), "down", true);

    // Create items
    Item* sword = new Item("sword", "A sharp sword");
    north_of_house->addItem(sword);

    Item* axe = new Item("axe", "A strong axe");
    clearing1->addItem(axe);

    Item* redKey = new Item("red key", "Key to open red doors");
    west_of_house->addItem(redKey);

    Item* greenKey = new Item("green key", "Key to open green doors");
    behind_house->addItem(greenKey);

    // Create character
    Character* troll = new Character("troll", "A huge troll", 150);
    south_of_house->addCharacter(troll);

    Character* joker = new Character("joker", "A smiling joker wearing a dark suit", 80);
    secret_chamber->addCharacter(joker);

    // Create door
    Door* door1 = new Door(north_of_house.get(), secret_chamber.get(), "north", "A locked wooden door.", redKey);
    std::shared_ptr<Door> sharedDoor1(door1);
    north_of_house->addPassage("north", sharedDoor1);

    Door* door2 = new Door(behind_house.get(), kitchen.get(), "west", "A locked wooden door.", greenKey);
    std::shared_ptr<Door> sharedDoor2(door2);
    behind_house->addPassage("west", sharedDoor2);



    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
