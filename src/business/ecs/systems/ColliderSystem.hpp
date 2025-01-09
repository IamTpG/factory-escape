#ifndef _COLLIDER_SYSTEM_HPP_
#define _COLLIDER_SYSTEM_HPP_

#include <raylib.h>

#include "../Core/System.hpp"

/// @brief System class to check for collisions
class ColliderSystem : public System {
public:
    virtual std::string ToString() const override;

public:
    Vector2 CollideWithOther(const Entity &entity);
};


#endif // _COLLIDER_SYSTEM_HPP_