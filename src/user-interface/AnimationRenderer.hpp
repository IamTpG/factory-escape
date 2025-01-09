#ifndef _ANIMATION_RENDERER_HPP_
#define _ANIMATION_RENDERER_HPP_

#include "../models/Object.hpp"
#include "../business/ecs/components/Renderable.hpp"
#include "../business/ecs/components/Animation.hpp"
#include "../business/ecs/components/Transform.hpp"

class AnimationRenderer : public Object {
public:
    virtual std::string ToString() const override;

public:
    void render(const Renderable &renderable, const Animation &animation, const Transform2 &transform);
};

#endif // _ANIMATION_RENDERER_HPP_