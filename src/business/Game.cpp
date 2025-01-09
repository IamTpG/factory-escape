#include "Game.hpp"
#include "../models/Config.hpp"

#include "ecs/core/Coordinator.hpp"

#include "../data-access/LevelProvider.hpp"

#include "Factory.hpp"
#include "CharacterInputHandler.hpp"
#include "DraggableTileInputHandler.hpp"

std::string Game::ToString() const
{
    return "Game";
}

void Game::Init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(GAME_FPS);

    _colliderSystem = Factory::GetInstance()->CreateColliderSystem();
    _physicsSystem  = Factory::GetInstance()->CreatePhysicsSystem();
    _rendererSystem = Factory::GetInstance()->CreateRendererSystem();

    LevelProvider levelProvider;
    level = levelProvider.next(0);
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        HandleInput();
        Update();
        Render();
    }
}

void Game::Shutdown()
{
    level->Destroy();
    delete level;
    level = nullptr;

    CloseWindow();
}

void Game::HandleInput()
{
    CharacterInputHandler characterHandler;
    characterHandler.next(level->character);

    static Entity draggingEntity = MAX_ENTITIES;
    DraggableTileInputHandler draggableTileHandler;

    if (draggingEntity == MAX_ENTITIES) {
        for (Entity tile : level->draggableTiles) {
            if (draggableTileHandler.next(tile)) {
                draggingEntity = tile;
                break;
            }
        }
    }
    else {
        if (!draggableTileHandler.next(draggingEntity)) {
            draggingEntity = MAX_ENTITIES;
        }
    }

    // Temporary key to restart level
    if (IsKeyPressed(KEY_R)) {
        level->Destroy();
        delete level;

        LevelProvider levelProvider;
        level = levelProvider.next(0);
    }

}

void Game::Update()
{
    float deltaTime = GetFrameTime();
    _physicsSystem->Update(deltaTime);
}

void Game::Render()
{
    BeginDrawing();
        ClearBackground(Color{255, 236, 214, 255});
        _rendererSystem->Update();
    EndDrawing();
}
