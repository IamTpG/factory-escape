#ifndef _TEXTURE_RENDERER_HPP_
#define _TEXTURE_RENDERER_HPP_

#include "../models/Object.hpp"
#include "../business/ecs/components/Renderable.hpp"
#include "../business/ecs/components/Transform.hpp"

class TextureRenderer : public Object {
public:
    virtual std::string ToString() const override;

public:
    void render(const Renderable &renderable, const Transform2 &transform);
};

#endif // _TEXTURE_RENDERER_HPP_