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
protected:
    int _index;
    // Collider _collider;      // hitbox
    // Rigidbody rigidbody;     // physics body
    int _currentAnimationIndex;
    vector<Animation> _animations;
public:
    Rectangle position;
public:
    Object();
    ~Object();

public:
    int GetIndex() const;
    int GetCurrentAnimationIndex() const;
    Animation GetCurrentAnimation() const;
    Rectangle GetPosition() const;

    void SetCurrentAnimation(int pIndex);
    void SetAnimationCount(int pCount);
    void SetPosition(Rectangle pPosition);

    /// @brief Add a sprite animation to vector<> _animations to _animations[index]
    void AddAnimation(int index, string imagePath, int row, int col, int width, int height, int amount, int framePerSecond);
};

#endif // OBJECT_HPP
