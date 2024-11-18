#include "Object.hpp"

#include "../DA/AnimationProvider.hpp"
#include "../GUI/AnimationRenderer.hpp"

#include <iostream>

using std::cout;

Object::Object()
{
    _currentAnimation = -1;
    _index = Physic::getObjectCount();
    Physic::addObjectCount();
}

Object::~Object()
{

}

Rectangle Object::position() const
{
    return _position;
}

int Object::index() const
{
    return _index;
}

int Object::currentAnimation() const
{
    return _currentAnimation;
}

Animation Object::animation() const
{
    return _animations[_currentAnimation];
}

void Object::setPosition(Rectangle value)
{
    _position = value;
}

void Object::setCurrentAnimation(int value)
{
    _currentAnimation = value;
}

void Object::setAnimationCount(int value)
{
    _animations.resize(value);
}

void Object::addAnimation(int animationIndex, string imagePath, int row, int col, int width, int height, int amount, int framePerSecond)
{
    AnimationProvider provider;
    _animations[animationIndex] = provider.next(imagePath, row, col, width, height, amount, framePerSecond);
}

void Object::setAnimation(int animationIndex)
{
    _currentAnimation = animationIndex;

    // if (_currentAnimation != animationIndex) {
    //     _currentAnimation = animationIndex;

    //     AnimationRenderer renderer;
    //     renderer.next(_animations[animationIndex], _position);
    // }
}

// void Object::draw()
// {
//     _animations[_currentAnimation].drawSpriteAnimationPro(_position, Vector2{ 0 }, 0.0f, WHITE);
// }
