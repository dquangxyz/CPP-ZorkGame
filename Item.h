#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &, std::string );

    Item(const std::string &, const std::string &, std::shared_ptr<Command>, std::string );

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);
    void showDescription();
    std::string getName() const;
    std::string getTag() const;


protected:
    std::shared_ptr<Command> useCommand;
    std::string tag;

};

#endif //ZOORK_ITEM_H
