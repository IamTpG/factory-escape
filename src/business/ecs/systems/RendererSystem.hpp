#ifndef _RENDERER_SYSTEM_HPP_
#define _RENDERER_SYSTEM_HPP_

#include "../Core/System.hpp"

/// @brief System class to handle rendering
class RendererSystem : public System {
public:
    std::string ToString() const override;

public:
    virtual void Update(float deltaTime) override;
};

#endif // _RENDERER_SYSTEM_HPP_