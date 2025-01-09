#ifndef _ANIMATION_PROVIDER_HPP_
#define _ANIMATION_PROVIDER_HPP_

#include "../models/Object.hpp"

#include "../business/ecs/components/Animation.hpp"

class AnimationProvider : public Object {
public:
    virtual std::string ToString() const override;

public:
    Animation next(std::string path);
};

#endif // _ANIMATION_PROVIDER_HPP_