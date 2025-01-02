#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include <raylib.h>

/// @brief Entity's component
struct Renderable {
    Rectangle rect;
    Texture2D texture;
};

#endif // _RENDERABLE_HPP_