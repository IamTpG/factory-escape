#ifndef _RENDERABLE_PROVIDER_HPP_
#define _RENDERABLE_PROVIDER_HPP_

#include <raylib.h>
#include <memory>
#include <unordered_map>

#include "../models/Object.hpp"
#include "../business/ecs/components/Renderable.hpp"

/// @brief Class to read texture from a file
class RenderableProvider : public Object {
public:
    virtual std::string ToString() const override;

public:
    Renderable next(std::string path, Rectangle rect = Rectangle{0, 0, 0, 0});
};

#endif // _RENDERABLE_PROVIDER_HPP_