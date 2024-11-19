#include "UserInputHandler.hpp"
#include "../BUS/Physic.hpp"

#include <raylib.h>

UserInputHandler::UserInputHandler()
{
    // Do nothing
}

UserInputHandler::~UserInputHandler()
{
    // Do nothing
}

void UserInputHandler::next(CommandListener &listener)
{
    bool isWalking = false;

    if (IsKeyDown(KEY_RIGHT)) {
        listener.goRight();
        isWalking = true;
    }
    
    if (IsKeyDown(KEY_LEFT)) {
        listener.goLeft();
        isWalking = true;
    }
    
    if (IsKeyDown(KEY_UP)) {
        listener.goUp();
        isWalking = true;
    }

    if (false == isWalking) {
        listener.goNowhere();
    }
}