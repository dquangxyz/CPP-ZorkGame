#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "Player.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room>);

    void run();

private:
    bool gameOver = false;
    Player *player;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand(std::vector<std::string>);
    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleQuitCommand(std::vector<std::string>);
    void handleInventoryCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);
    void handleHealthCommand();
    void handleOpenCommand(std::vector<std::string>);
    void handleTalkCommand(const std::vector<std::string>& arguments);
    void handleAttackCommand(const std::vector<std::string>& arguments);
    void handleScoreCommand();
    static std::vector<std::string> tokenizeString(const std::string&);

    static std::string makeLowercase(std::string);
};


#endif //ZOORK_ZOORKENGINE_H
