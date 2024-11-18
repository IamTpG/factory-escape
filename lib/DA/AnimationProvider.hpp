#ifndef ANIMATION_PROVIDER_HPP
#define ANIMATION_PROVIDER_HPP

#include <vector>

#include "../DTO/Animation.hpp"

using std::vector;

class AnimationProvider {
public:
    /// @brief Load an animation from a path with given informations
    /// @return The animation loaded
    Animation next(string imagePath, int row, int col, int width, int height, int amount, int framePerSecond);
};

#endif // ANIMATION_PROVIDER_HPP