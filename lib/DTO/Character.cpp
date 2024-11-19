#include "Character.hpp"
#include "Define.hpp"

#include <iostream>

Character::Character()
{
    SetAnimationCount((int)Animation::Character::MAX_COUNT);

    AddAnimation((int)Animation::Character::IDLE_RIGHT, CHARACTER_PATH, 2, 0, 16, 16, 2, 2);
    AddAnimation((int)Animation::Character::IDLE_LEFT,  CHARACTER_PATH, 3, 0, 16, 16, 2, 2);
    AddAnimation((int)Animation::Character::WALK_RIGHT, CHARACTER_PATH, 6, 0, 16, 16, 4, 8);
    AddAnimation((int)Animation::Character::WALK_LEFT,  CHARACTER_PATH, 7, 0, 16, 16, 4, 8);

    Rectangle rect = Rectangle({
        (float)GetScreenWidth()  / 2,
        (float)GetScreenHeight() / 2,
        (float)64,
        (float)64
    });

    SetPosition(
        rect
    );

    Rectangle hitbox = Rectangle({
        rect.x + 8,
        rect.y,
        (float)48,
        (float)64
    });

    Physic::AddCollider(
        _index,
        Collider({
            true,
            (bool)Collider::Type::RECTANGLE,
            hitbox,
            0.0f
        })
    );

    Physic::AddRigidbody(
        _index,
        Rigidbody({
            true,                   // enabled
            CHARACTER_MASS,         // mass
            Vector2{0.0f, 0.0f},    // acceleration
            Vector2{0.0f, 0.0f},    // velocity
            false,                  // isGrounded
            false,                  // isContact
            true,                   // applyGravity
            CHARACTER_FRICTION,     // friction
            CHARACTER_BOUNCINESS    // bounciness
        })
    );

    SetIdleOff();
    SetWalkOff();

    SetState((int)Animation::Character::IDLE_RIGHT, true);
    SetCurrentAnimation((int)Animation::Character::IDLE_RIGHT);
}

Character::~Character()
{
    // do nothing
}

void Character::SetIdleOff()
{
    SetState((int)Animation::Character::IDLE_RIGHT, false);
    SetState((int)Animation::Character::IDLE_LEFT,  false);
}

void Character::SetWalkOff()
{
    SetState((int)Animation::Character::WALK_RIGHT, false);
    SetState((int)Animation::Character::WALK_LEFT,  false);
}

bool Character::GetState(int pIndex) const
{
    return _states[pIndex];
}

void Character::SetState(int pIndex, bool value)
{
    _states[pIndex] = value;
}

void Character::SetAnimationCount(int pCount)
{
    Object::SetAnimationCount(pCount);
    _states.resize(pCount);
}

void Character::goRight()
{
    Physic::SetRigidbodyVelocityX(_index, CHARACTER_SPEED_X);
    SetCurrentAnimation((int)Animation::Character::WALK_RIGHT);
}

void Character::goLeft()
{
    Physic::SetRigidbodyVelocityX(_index, -CHARACTER_SPEED_X);
    SetCurrentAnimation((int)Animation::Character::WALK_LEFT);
}

void Character::goUp()
{
    if (Physic::GetRigidbody(_index).isGrounded) {
        Physic::SetRigidbodyVelocityY(_index, CHARACTER_SPEED_Y);
    }
}

void Character::goNowhere()
{
    if (Physic::GetRigidbody(_index).velocity.x == 0.0f && Physic::GetRigidbody(_index).velocity.y == 0.0f) {
        if (_currentAnimationIndex == (int)Animation::Character::WALK_RIGHT) {
            SetCurrentAnimation((int)Animation::Character::IDLE_RIGHT);
        }
        else if (_currentAnimationIndex == (int)Animation::Character::WALK_LEFT) {
            SetCurrentAnimation((int)Animation::Character::IDLE_LEFT);
        }
    }
}
