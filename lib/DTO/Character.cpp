#include "Character.hpp"
#include "Define.hpp"

#include <iostream>

Character::Character()
{
    setAnimationCount((int)Animation::Character::MAX_COUNT);

    addAnimation((int)Animation::Character::IDLE_RIGHT, CHARACTER_PATH, 2, 0, 16, 16, 2, 3);
    addAnimation((int)Animation::Character::IDLE_LEFT,  CHARACTER_PATH, 3, 0, 16, 16, 2, 3);
    addAnimation((int)Animation::Character::WALK_RIGHT, CHARACTER_PATH, 6, 0, 16, 16, 4, 3);
    addAnimation((int)Animation::Character::WALK_LEFT,  CHARACTER_PATH, 7, 0, 16, 16, 4, 3);

    setPosition(
        Rectangle({
            (float)GetScreenWidth()  / 2,
            (float)GetScreenHeight() / 2,
            (float)64,
            (float)64
        })
    );

    Rectangle hitbox = Rectangle({
        (float)_position.x + 8,
        (float)_position.y,
        (float)48,
        (float)64
    });

    Physic::addCollider(
        _index,
        Collider({
            true,
            (bool)Collider::Type::RECTANGLE,
            hitbox,
            0.0f
        })
    );

    Physic::addRigidbody(
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

    _setIdleOff();
    _setMoveOff();

    setState((int)Animation::Character::IDLE_RIGHT, true);
    setAnimation((int)Animation::Character::IDLE_RIGHT);
}

Character::~Character()
{
    // do nothing
}

void Character::_setIdleOff()
{
    setState((int)Animation::Character::IDLE_RIGHT, false);
    setState((int)Animation::Character::IDLE_LEFT,  false);
}

void Character::_setMoveOff()
{
    setState((int)Animation::Character::WALK_RIGHT, false);
    setState((int)Animation::Character::WALK_LEFT,  false);
}

bool Character::state(int index) const
{
    return _states[index];
}

void Character::setState(int index, bool value)
{
    _states[index] = value;
}

void Character::setAnimationCount(int count)
{
    Object::setAnimationCount(count);
    _states.resize(count);
}

// void Character::move()
// {
//     if (state((int)Animation::Character::IDLE_RIGHT) == true) {
//         setAnimation((int)Animation::Character::IDLE_RIGHT);
//     }
//     if (state((int)Animation::Character::IDLE_LEFT) == true) {
//         setAnimation((int)Animation::Character::IDLE_LEFT);
//     }
    
//     if (state((int)Animation::Character::WALK_RIGHT) == true) {
//         setAnimation((int)Animation::Character::WALK_RIGHT);
//     }
//     if (state((int)Animation::Character::WALK_LEFT) == true) {
//         setAnimation((int)Animation::Character::WALK_LEFT);
//     }

//     if (_moveLeft == true) {
//         setAnimation(_animationMoveLeft);
//         setSpeedX(-Character::SPEED_X);
//     }
//     if (_moveRight == true) {
//         setAnimation(_animationMoveRight);
//         setSpeedX(Character::SPEED_X);
//     }
//     if (_moveUp == true) {
//         setAnimation(_animationMoveUp);
//         setSpeedY(-Character::SPEED_Y);
//     }
//     if (_moveDown == true) {
//         setAnimation(_animationMoveDown);
//         setSpeedY(Character::SPEED_Y);
//     }

//     Rectangle currentPosition = position();
//     setPosition(Rectangle{currentPosition.x + speedX(),
//                           currentPosition.y + speedY(),
//                           currentPosition.width,
//                           currentPosition.height});

//     draw();
//     setSpeedX(0);
//     setSpeedY(0);
// }
