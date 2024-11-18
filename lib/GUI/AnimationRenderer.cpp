#include "AnimationRenderer.hpp"

void AnimationRenderer::next(const Animation &animation, Rectangle dest, Vector2 origin /*= Vector2{0}*/, float rotation /*= 0.0f*/, Color tint /*= WHITE*/)
{
    int index = (int)(GetTime() * animation.framePerSecond) % (int)animation.rectangles.size();
    Rectangle source = animation.rectangles[index];
    DrawTexturePro(animation.atlas, source, dest, origin, rotation, tint);
}
