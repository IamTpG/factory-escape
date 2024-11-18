#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <raylib.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

class Animation {
public:
    enum class Character {
        IDLE_RIGHT  = 0,
        IDLE_LEFT   = 1,
        WALK_RIGHT  = 2,
        WALK_LEFT   = 3,
        JUMP_RIGHT  = 4,
        JUMP_LEFT   = 5,
        MAX_COUNT   = 6,
    };

public:
    Texture2D atlas;
    vector<Rectangle> rectangles;
    int framePerSecond;
public:
    Animation();
    Animation(Texture2D atlas, const vector<Rectangle> &rectangles, int framePerSecond);
    ~Animation();
};

#endif // ANIMATION_HPP
