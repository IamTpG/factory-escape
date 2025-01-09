#include "TextureRenderer.hpp"
#include <raymath.h>

std::string TextureRenderer::ToString() const
{
    return "TextureRenderer";
}

void TextureRenderer::render(const Renderable &renderable, const Transform2 &transform)
{
    Rectangle source = renderable.rect;

    Rectangle dest = Rectangle {
        .x      = transform.position.x,
        .y      = transform.position.y,
        .width  = renderable.rect.width  * transform.scale.x,
        .height = renderable.rect.height * transform.scale.y
    };

    DrawTexturePro(renderable.texture, source, dest, Vector2Zero(), transform.rotation, WHITE);

    // no scale, no rotation
    // DrawTextureV(renderable.texture, transform.position, WHITE);
}