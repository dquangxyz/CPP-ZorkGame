#include "ZOOrkEngine.h"
#include "Door.h"

#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect") || (command == "examine")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "inventory") {
            handleInventoryCommand(arguments);
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "health") {
            handleHealthCommand();
        } else if (command == "talk") {
            if (arguments.size() > 1 && arguments[0] == "to") {
                arguments.erase(arguments.begin());
            }
            handleTalkCommand(arguments);
        } else if (command == "attack") {
            if (arguments.size() > 1 && arguments[0] == "the") {
                arguments.erase(arguments.begin());
            }
            handleAttackCommand(arguments);
        } else if (command == "open") {
            if (arguments.size() > 1 && arguments[0] == "the") {
                arguments.erase(arguments.begin());
            }
            handleOpenCommand(arguments);
        } else if (command == "score") {
            handleScoreCommand();
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}
void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    // Check if there is a door in the specified direction
    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    if (std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(passage)) {
        if (door->isDoorOpen()) {
            std::cout << "You have opened the door.\n";
            player->setCurrentRoom(passage->getTo());
            passage->enter();
        } else {
            std::cout << "The door is locked. You need a key to open it.\n";
            return; // Return without moving to the next room
        }
    } else {
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    }
}


void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();
    std::string doorDirection = currentRoom->getDoorDirection();

    if (arguments.empty()) {
        // Display if there is a door
        currentRoom->enter();
        if (currentRoom->getName() != "forest" && currentRoom->getName() != "clearing") {
            if (doorDirection == "unknown") {
                std::cout << "There is no door in this room.\n";
            } else {
                std::cout << "There is a door in the " << doorDirection << " of this room.\n";
            }
        }

        // Display if there is any item
        if (!currentRoom->items.empty()) {
            std::cout << "Items in the room:\n";
            for (Item* item : currentRoom->items) {
                if (item != nullptr) {
                    std::cout << "- " << item->getName() << '\n';
                }
            }
        }

        // Display if there is any character
        if (!currentRoom->characters.empty()) {
            std::cout << "Characters in the room:\n";
            for (Character* character : currentRoom->characters) {
                if (character != nullptr) {
                    std::cout << "- " << character->getName() << '\n';
                }
            }
        }

    } else {
        std::string target = arguments[0];
        Item* item = currentRoom->getItem(target);

        if (item) {
            item->showDescription();
        } else if (target == "door") {  // Check if the target is "door"
            if (doorDirection == "unknown") {
                std::cout << "There is no door in this room.\n";
            } else {
                auto passage = currentRoom->getPassage(doorDirection);
                std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(passage);
                std::cout << door->getDescription() << '\n';
            }
        } else {
            Character* character = currentRoom->getCharacter(target);
            if (character) {
                std::cout << character->getDescription() << '\n';
                character->talk();
            } else {
                std::cout << "You don't see that here.\n";
            }
        }
    }
}


void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Please specify the item you want to take.\n";
        return;
    }

    std::string itemName;
    // Combine all arguments to form the item name
    for (const std::string& arg : arguments) {
        itemName += arg + " ";
    }
    // Remove trailing whitespace
    itemName = itemName.substr(0, itemName.size() - 1);

    Room* currentRoom = player->getCurrentRoom();
    Item* item = currentRoom->getItem(itemName);

    if (!item) {
        // Check if the item name contains the word 'key'
        if (itemName.find("key") != std::string::npos) {
            std::cout << "The key '" << itemName << "' is not in this room.\n";
        } else {
            std::cout << "The item '" << itemName << "' is not in this room.\n";
        }
        return;
    }

    player->addItem(item);
    currentRoom->removeItem(itemName);
    std::cout << "You have taken the " << itemName << ".\n";
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Please specify the item you want to drop.\n";
        return;
    }

    std::string itemName;
    // Combine all arguments to form the item name
    for (const std::string& arg : arguments) {
        itemName += arg + " ";
    }
    // Remove trailing whitespace
    itemName = itemName.substr(0, itemName.size() - 1);

    Room* currentRoom = player->getCurrentRoom();
    Item* item = player->getItem(itemName);

    if (!item) {
        std::cout << "You don't have the item '" << itemName << "'.\n";
        return;
    }
    if (player->getCurrentWeapon() == item) {
        player->setCurrentWeapon(nullptr);
    }
    player->removeItem(itemName);
    player->addDroppedItem(item);
    currentRoom->addItem(item);
}


void ZOOrkEngine::handleInventoryCommand(std::vector<std::string> arguments) {
    player->showInventory();
}

void ZOOrkEngine::handleHealthCommand() {
    player->showHealth();
}
void ZOOrkEngine::handleScoreCommand() {
    std::cout << "Score: " << player->getScore() << '\n';
}
void ZOOrkEngine::handleTalkCommand(const std::vector<std::string>& arguments) {
    if (arguments.empty()) {
        std::cout << "Whom do you want to talk to?\n";
        return;
    }

    std::string characterName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    Character* character = currentRoom->getCharacter(characterName);

    if (character) {
        character->talk();
    } else {
        std::cout << "There is no character named '" << characterName << "' in this room.\n";
    }
}

void ZOOrkEngine::handleAttackCommand(const std::vector<std::string>& arguments) {
    if (arguments.empty()) {
        std::cout << "Whom do you want to attack?\n";
        return;
    }

    std::string characterName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    Character* character = currentRoom->getCharacter(characterName);

    if (character) {
        player->attack(character);
        if (character->getHealth() > 0){
            character->counterAttack(player, character->getAttackDamage());
            if (player->getHealth() <= 0){
                gameOver = true;
                return;
            }
        }
    } else {
        std::cout << "There is no character named '" << characterName << "' in this room.\n";
    }
}



void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        std::cout << "Your final score is " << player->getScore() << '\n';
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

void ZOOrkEngine::handleOpenCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Open what?\n";
        return;
    }
    std::string target = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    std::string doorDirection = currentRoom->getDoorDirection();
    auto passage = currentRoom->getPassage(doorDirection);
    if (std::shared_ptr<Door> door = std::dynamic_pointer_cast<Door>(passage)) {
        if (door->isDoorOpen()) {
            std::cout << "The door is already open.\n";
        } else {
            if (player->hasItem(door->getRequiredKey()->getName())) {
                std::cout << "You have opened the door.\n";
                door->setOpenState(true);
                player->setScore(player->getScore()+20);
            } else {
                std::cout << "The door is locked. You need a key to open it.\n";
            }
        }
    } else {
        std::cout << "You can't open that.\n";
    }
}

void ZOOrkEngine::handleUseCommand(const std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "What do you want to use?\n";
        return;
    }

    std::string itemName = arguments[0];
    Item* item = player->getItem(itemName);

    if (!item) {
        std::cout << "You don't have the item '" << itemName << "'.\n";
        return;
    } else if (item->getTag() == "weapon"){
        player->setCurrentWeapon(item);
        std::cout << "You are now using the " << itemName << ".\n";
    } else if (item->getTag() == "drink"){
        if (item->getName() == "soda"){
            player->increaseHealth(10);
            std::cout << "You have recovered 10 HP.\n";
        } else if (item->getName() == "juice"){
            player->increaseHealth(20);
            std::cout << "You have recovered 20 HP.\n";
        } else if (item->getName() == "beer"){
            player->increaseHealth(30);
            std::cout << "You have recovered 30 HP.\n";
        }
        player->showHealth();
    } else {
        std::cout << "Impossible to use this item";
    }

}


