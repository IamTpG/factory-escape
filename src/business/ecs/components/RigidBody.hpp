#ifndef _RIGID_BODY_HPP_
#define _RIGID_BODY_HPP_

#include <raylib.h>

/// @brief Entity's component
struct RigidBody {
    Vector2 acceleration;
    Vector2 velocity;
};

#endif // _RIGID_BODY_HPP_