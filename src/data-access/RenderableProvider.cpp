#include "RenderableProvider.hpp"
#include <raymath.h>

std::string RenderableProvider::ToString() const
{
    return "RenderableProvider";
}

Renderable RenderableProvider::next(std::string path, Rectangle rect /* = Rectangle{0, 0, 0, 0} */)
{
    Image image = LoadImage(path.c_str());
    Renderable renderable = Renderable {
        .rect    = rect,
        .texture = LoadTextureFromImage(image)
    };

    if (FloatEquals(rect.height, 0.0f) && FloatEquals(rect.width, 0.0f)) {
        renderable.rect.width  = renderable.texture.width;
        renderable.rect.height = renderable.texture.height;
    }

    UnloadImage(image);
    return renderable;
}
