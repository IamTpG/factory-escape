#include "AnimationProvider.hpp"

Animation AnimationProvider::next(string imagePath, int row, int col, int width, int height, int amount, int framePerSecond)
{
    Image image = LoadImage(imagePath.c_str());
    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);

    vector<Rectangle> rectangles(amount);
    for (int i = 0; i < amount; i++) {
        rectangles[i] = Rectangle{(float)i * width + col * width, (float)row * height, (float)width, (float)height};
    }

    return Animation(texture, rectangles, framePerSecond);
}
