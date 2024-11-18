#include "Animation.hpp"

#include <iostream>

using std::cout;

Animation::Animation()
{
    framePerSecond = 0;
}

Animation::Animation(Texture2D pAtlas, const vector<Rectangle> &pRectangles, int pFramePerSecond)
{
    atlas = pAtlas;
    rectangles = pRectangles;
    framePerSecond = pFramePerSecond;
}

Animation::~Animation()
{
    // UnloadTexture(_atlas);
}
