#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d, std::string tag)
    : GameObject(n, d),useCommand(std::make_shared<NullCommand>()), tag(std::move(tag)) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, std::string tag)
    : GameObject(n, d),useCommand(std::move(c)), tag(std::move(tag)) {}

void Item::use() {
    useCommand->execute();
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}
void Item::showDescription(){
    std::cout << description << '\n';
}
std::string Item::getName() const {
    return name;
}
std::string Item::getTag() const {
    return tag;
}