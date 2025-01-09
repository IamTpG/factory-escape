#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include <raylib.h>
#include <vector>

/**
 * Each state will have its own FPS
 * The currentState is used for keep track of states
 */
struct Animation {
    std::vector<int> framePerSecond;
    std::vector<std::vector<Rectangle>> rectangles;
    int currentState; // 0 <= currentState < rectangles.size()
};

enum class CharacterAnimation {
    IDLE_RIGHT  = 0,
    IDLE_LEFT   = 1,
    GO_RIGHT    = 2,
    GO_LEFT     = 3
};

#endif // _ANIMATION_HPP_