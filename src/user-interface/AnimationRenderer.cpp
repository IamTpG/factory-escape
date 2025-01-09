#include "AnimationRenderer.hpp"

#include <raylib.h>
#include <raymath.h>

std::string AnimationRenderer::ToString() const
{
    return "AnimationRenderer";
}

void AnimationRenderer::render(const Renderable &renderable, const Animation &animation, const Transform2 &transform)
{
    int currentState = animation.currentState;
    int id = (int)(GetTime() * animation.framePerSecond[currentState]) % (int)animation.rectangles[currentState].size();

    Rectangle source = animation.rectangles[currentState][id];

    Rectangle dest = Rectangle {
        .x      = transform.position.x,
        .y      = transform.position.y,
        .width  = animation.rectangles[currentState][id].width  * transform.scale.x,
        .height = animation.rectangles[currentState][id].height * transform.scale.y
    };

    DrawTexturePro(renderable.texture, source, dest, Vector2Zero(), transform.rotation, WHITE);
}
