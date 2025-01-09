#include "AnimationProvider.hpp"

#include <fstream>

std::string AnimationProvider::ToString() const
{
    return "AnimationProvider";
}

Animation AnimationProvider::next(std::string path)
{
    std::ifstream reader;
    reader.open(path, std::ios::in);

    if (!reader.is_open()) {
        printf("Cannot read \"%s\"\n", path.c_str());
        return Animation{};
    }

    Animation animation;
    animation.currentState = 0;

    int animationCount;
    int rectangleCount;
    std::vector<std::vector<Rectangle>> &rectangles = animation.rectangles;
    std::vector<int> &framePerSecond = animation.framePerSecond;

    reader >> animationCount;
    rectangles.resize(animationCount);
    framePerSecond.resize(animationCount);

    for (int i = 0; i < animationCount; i++) {
        reader >> rectangleCount >> framePerSecond[i];
        rectangles[i].resize(rectangleCount);

        for (int j = 0; j < rectangleCount; j++) {
            Rectangle &rectangle = rectangles[i][j];
            reader >> rectangle.x >> rectangle.y >> rectangle.width >> rectangle.height;
        }
    }

    reader.close();
    return animation;
}
