#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "CommandListener.hpp"
#include "Object.hpp"

class Character : public CommandListener, public Object{
private:
    vector<bool> _states;
public:
    Character();
    ~Character();
public:
    bool GetState(int pIndex) const;
    void SetState(int pIndex, bool pState);
    void SetAnimationCount(int pCount);

    void SetIdleOff();
    void SetWalkOff();
public:
    void goRight()      override;
    void goLeft()       override;
    void goUp()         override;
    void goNowhere()    override;
};

#endif // CHARACTER_HPP
