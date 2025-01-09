#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include <raylib.h>
#include <vector>

struct Animation {
    int framePerSecond;
    std::vector<Rectangle> rectangles;
    std::vector<int> states; // states[i] is the start index of state #i in rectangles[]
    int currentState;
};

#endif // _ANIMATION_HPP_