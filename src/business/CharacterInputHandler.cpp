#include "CharacterInputHandler.hpp"
#include "../models/Config.hpp"

#include "ecs/core/Coordinator.hpp"
#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Animation.hpp"

#include <raymath.h>

std::string CharacterInputHandler::ToString() const
{
    return "CharacterInputHandler";
}

void CharacterInputHandler::next(Entity character)
{
    /*
        Everytime a key pressed (WASD or arrow keys),
        we provide the character an init speed (x/y).
        Then the physics system will handle the rest.
    */

    RigidBody &rigidBody = Coordinator::GetInstance()->GetComponent<RigidBody>(character);
    Animation &animation = Coordinator::GetInstance()->GetComponent<Animation>(character);

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        rigidBody.velocity.x = -CHARACTER_SPEED_X;
        animation.currentState = (int)CharacterAnimation::GO_LEFT;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        rigidBody.velocity.x = CHARACTER_SPEED_X;
        animation.currentState = (int)CharacterAnimation::GO_RIGHT;
    }

    if (FloatEquals(rigidBody.velocity.y, 0.0f) && (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) {
        rigidBody.velocity.y = -CHARACTER_SPEED_Y;
    }

    if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_LEFT)) {
        rigidBody.velocity.x = 0;
        animation.currentState = (int)CharacterAnimation::IDLE_LEFT;
    }

    if (IsKeyReleased(KEY_D) || IsKeyReleased(KEY_RIGHT)) {
        rigidBody.velocity.x = 0;
        animation.currentState = (int)CharacterAnimation::IDLE_RIGHT;
    }
}