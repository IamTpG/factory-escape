#ifndef _PHYSICS_SYSTEM_HPP_
#define _PHYSICS_SYSTEM_HPP_

#include "../Core/System.hpp"

/// @brief System class to handle game physics
class PhysicsSystem : public System {
public:
    std::string ToString() const override;

public:
    virtual void Update(float deltaTime = 0.0f) override;
};

#endif // _PHYSICS_SYSTEM_HPP_