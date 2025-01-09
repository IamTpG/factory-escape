#include "LevelProvider.hpp"
#include "../models/Config.hpp"

#include "../business/Factory.hpp"

std::string LevelProvider::ToString() const
{
    return "LevelProvider";
}

Level* LevelProvider::next(int levelId)
{
    std::string path = LEVEL_PATH + std::to_string(levelId);

    if (levelId != 0) {
        return nullptr;
    }

    Level* level = new Level();

    Entity &character                   = level->character;
    std::vector<Entity> &fixedTiles     = level->fixedTiles;
    std::vector<Entity> &draggableTiles = level->draggableTiles;

    character = Factory::GetInstance()->CreateCharacter(Vector2{ 6, TILE_HEIGHT_COUNT / 2});

    // Fixed (undraggble) solid tiles
    for (int i = 0; i < 5; i++) {
        Entity tile = Factory::GetInstance()->CreateSolidTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 3}, 41);
        fixedTiles.push_back(tile);
    }
    for (int i = 5; i < 9; i++) {
        Entity tile = Factory::GetInstance()->CreateSolidTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 2}, 41);
        fixedTiles.push_back(tile);
    }

    // Draggable tiles
    for (int i = 9; i < TILE_WIDTH_COUNT; i++) {
        Entity tile = Factory::GetInstance()->CreateDraggableTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 3}, 44);
        draggableTiles.push_back(tile);
    }

    return level;
}