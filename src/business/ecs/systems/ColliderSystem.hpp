#ifndef _COLLIDER_SYSTEM_HPP_
#define _COLLIDER_SYSTEM_HPP_

#include <raylib.h>

#include "../Core/System.hpp"

/// @brief System class to check for collisions
class ColliderSystem : public System {
public:
    std::string ToString() const override;

public:
    virtual void Update(float deltaTime = 0.0f) override;
    Vector2 CollideWithOther(const Entity &entity);
};


#endif // _COLLIDER_SYSTEM_HPP_