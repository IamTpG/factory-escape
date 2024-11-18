#ifndef ANIMATION_RENDERER_HPP
#define ANIMATION_RENDERER_HPP

#include "../DTO/Animation.hpp"

class AnimationRenderer {
public:
    void next(const Animation &animation, Rectangle dest, Vector2 origin = Vector2{0}, float rotation = 0.0f, Color tint = WHITE);
};

#endif // ANIMATION_RENDERER_HPP
