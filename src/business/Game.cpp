#include "Game.hpp"
#include "../models/Config.hpp"

#include "ecs/core/Coordinator.hpp"

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

    _character = Factory::GetInstance()->CreateCharacter(Vector2{ 6, TILE_HEIGHT_COUNT / 2});

    _tiles.reserve(TILE_WIDTH_COUNT);

    // Fixed (undraggble) solid tiles
    for (int i = 0; i < 5; i++) {
        Entity tile = Factory::GetInstance()->CreateSolidTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 3}, 41);
        _tiles.push_back(tile);
    }
    for (int i = 5; i < 9; i++) {
        Entity tile = Factory::GetInstance()->CreateSolidTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 2}, 41);
        _tiles.push_back(tile);
    }

    // Draggable tiles
    for (int i = 9; i < TILE_WIDTH_COUNT; i++) {
        Entity tile = Factory::GetInstance()->CreateDraggableTile(Vector2{(float)i, (float)TILE_HEIGHT_COUNT - 3}, 41);
        _tiles.push_back(tile);
    }
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
    CloseWindow();
}

void Game::HandleInput()
{
    CharacterInputHandler characterHandler;
    characterHandler.next(_character);

    bool dragging = false;
    DraggableTileInputHandler draggableTileHandler;
    for (Entity tile : _tiles) {
        if (dragging) {
            break;
        }

        dragging = draggableTileHandler.next(tile);
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
