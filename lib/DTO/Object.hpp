#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <raylib.h>
#include <vector>
#include <string>

#include "../BUS/Physic.hpp"
#include "Animation.hpp"

using std::vector;
using std::string;

class Object {
public:
    Rectangle _position;
protected:
    int _index;
    // Collider _collider;      // hitbox
    // Rigidbody rigidbody;     // physics body
    int _currentAnimation;
    vector<Animation> _animations;
public:
    Object();
    ~Object();

public:
    int index() const;
    Rectangle position() const;
    int currentAnimation() const;
    Animation animation() const;

    void setPosition(Rectangle value);
    void setCurrentAnimation(int value);
    void setAnimationCount(int value);

    /// @brief Add a sprite animation to vector<> _animations to _animations[index]
    void addAnimation(int index, string imagePath, int row, int col, int width, int height, int amount, int framePerSecond);
    
    /// @brief Change the sprite animation to index and render it on the screen
    void setAnimation(int index);

    // void draw();
};

#endif // OBJECT_HPP
