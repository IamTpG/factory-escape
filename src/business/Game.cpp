#include "Game.hpp"
#include "../models/Config.hpp"

#include "ecs/core/Coordinator.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Collider.hpp"
#include "ecs/components/RigidBody.hpp"

#include "../data-access/LevelProvider.hpp"

#include "Factory.hpp"
#include "CharacterInputHandler.hpp"
#include "DraggableTileInputHandler.hpp"
#include "ButtonInputHandler.hpp"

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

    level->chararcterSpawnpoint = Coordinator::GetInstance()->GetComponent<Transform2>(level->character).position;
    level->characterMoving = false;
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

    if (level->characterMoving == false) {
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
    }

    ButtonInputHandler buttonHandler;
    bool playAction     = buttonHandler.next(level->playButton);
    bool replayAction   = buttonHandler.next(level->replayButton);
    bool restartAction  = buttonHandler.next(level->restartButton);

    if (playAction) {
        printf("Button PLAY pressed!\n");
        level->characterMoving = true;
    }

    if (replayAction) {
        printf("Button REPLAY pressed!\n");

        Vector2     &position = Coordinator::GetInstance()->GetComponent<Transform2>(level->character).position;
        Rectangle   &boundary = Coordinator::GetInstance()->GetComponent<Collider>(level->character).boundary;

        position = level->chararcterSpawnpoint;
        boundary.x = level->chararcterSpawnpoint.x;
        boundary.y = level->chararcterSpawnpoint.y;

        level->characterMoving = false;
    }

    if (restartAction) {
        printf("Button RESTART pressed!\n");
    }

    // Temporary key 'R' to restart level
    if (restartAction || IsKeyPressed(KEY_R)) {
        level->Destroy();
        delete level;

        LevelProvider levelProvider;
        level = levelProvider.next(0);

        level->chararcterSpawnpoint = Coordinator::GetInstance()->GetComponent<Transform2>(level->character).position;
        level->characterMoving = false;
    }
}

void Game::Update()
{
    if (level->characterMoving) {
        Coordinator::GetInstance()->GetComponent<RigidBody>(level->character).velocity.x = CHARACTER_SPEED_X;   
    }

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
