#ifndef _CHARACTER_INPUT_HANDLER_HPP_
#define _CHARACTER_INPUT_HANDLER_HPP_

#include "../models/Object.hpp"
#include "ecs/core/ECSTypes.hpp"

/// @brief Class to handle character movement
class CharacterInputHandler : public Object {
public:
    virtual std::string ToString() const override;

public:
    void next(Entity character);
};

#endif // _CHARACTER_INPUT_HANDLER_HPP_