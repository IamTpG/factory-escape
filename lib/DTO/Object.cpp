#include "Object.hpp"

#include "../DA/AnimationProvider.hpp"
#include "../GUI/AnimationRenderer.hpp"

#include <iostream>

using std::cout;

Object::Object()
{
    _currentAnimationIndex = -1;
    _index = Physic::GetObjectCount();
    Physic::AddObjectCount();
}

Object::~Object()
{
    // do nothing
}

int Object::GetIndex() const
{
    return _index;
}

int Object::GetCurrentAnimationIndex() const
{
    return _currentAnimationIndex;
}

Animation Object::GetCurrentAnimation() const
{
    return _animations[_currentAnimationIndex];
}

Rectangle Object::GetPosition() const
{
    return position;
}

void Object::SetCurrentAnimation(int pIndex)
{
    _currentAnimationIndex = pIndex;
}

void Object::SetAnimationCount(int pCount)
{
    _animations.resize(pCount);
}

void Object::AddAnimation(int pAnimationIndex, string pImagePath, int pRow, int pCol, int pWidth, int pHeight, int pAmount, int pFramePerSecond)
{
    AnimationProvider provider;
    _animations[pAnimationIndex] = provider.next(
        pImagePath, pRow, pCol, pWidth, pHeight, pAmount, pFramePerSecond
    );
}

void Object::SetPosition(Rectangle pPosition)
{
    position = pPosition;
}
