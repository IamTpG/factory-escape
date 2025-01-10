#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include <raylib.h>
#include <vector>

#include "Object.hpp"
#include "../business/ecs/core/ECSTypes.hpp"

class Level : public Object {
public:
    virtual std::string ToString() const override;

public:
    void Destroy();

public:
    Entity character;
    std::vector<Entity> fixedTiles;
    std::vector<Entity> draggableTiles;

    Vector2 chararcterSpawnpoint;
    bool characterMoving;

    Entity playButton, replayButton, restartButton;
};

#endif // _LEVEL_HPP_