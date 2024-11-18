#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Object.hpp"

class Character : public Object {
private:
    vector<bool> _states;
public:
    Character();
    ~Character();
public:
    bool state(int index) const;
    void setState(int index, bool value);
    void setAnimationCount(int count);

    void _setIdleOff();
    void _setMoveOff();

    // void move();
};

#endif // CHARACTER_HPP
