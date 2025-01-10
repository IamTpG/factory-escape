#ifndef _BUTTON_INPUT_HANDLER_HPP_
#define _BUTTON_INPUT_HANDLER_HPP_

#include "../models/Object.hpp"
#include "ecs/core/ECSTypes.hpp"

class ButtonInputHandler : public Object {
public:
    virtual std::string ToString() const override;

public:
    bool next(Entity button);
};

#endif // _BUTTON_INPUT_HANDLER_HPP_