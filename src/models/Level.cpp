#include "Level.hpp"

#include <raylib.h>
#include "../business/ecs/core/Coordinator.hpp"

std::string Level::ToString() const
{
    return "Level";
}

void Level::Destroy()
{
    Coordinator::GetInstance()->DestroyEntity(character);

    for (Entity &entity : fixedTiles) {
        Coordinator::GetInstance()->DestroyEntity(entity);
    }

    for (Entity &entity : draggableTiles) {
        Coordinator::GetInstance()->DestroyEntity(entity);
    }

    Coordinator::GetInstance()->DestroyEntity(playButton);
    Coordinator::GetInstance()->DestroyEntity(replayButton);
    Coordinator::GetInstance()->DestroyEntity(restartButton);
}