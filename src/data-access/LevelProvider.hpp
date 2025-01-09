#ifndef _LEVEL_PROVIDER_HPP_
#define _LEVEL_PROVIDER_HPP_

#include "../models/Object.hpp"
#include "../models/Level.hpp"

class LevelProvider : public Object {
public:
    virtual std::string ToString() const override;

public:
    Level* next(int levelId);
};

#endif // _LEVEL_PROVIDER_HPP_