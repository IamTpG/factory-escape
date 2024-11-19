#ifndef USER_INPUT_HANDLER_HPP
#define USER_INPUT_HANDLER_HPP

#include "../DTO/CommandListener.hpp"

class UserInputHandler {
public:
    UserInputHandler();
    ~UserInputHandler();
public:
    void next(CommandListener &listener);
};

#endif // USER_INPUT_HANDLER_HPP
