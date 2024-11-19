#include <iostream>
#include <raylib.h>

#include "../lib/DTO/Define.hpp"
#include "../lib/DTO/Character.hpp"
#include "../lib/DTO/Animation.hpp"

#include "../lib/DA/UserInputHandler.hpp"

#include "../lib/BUS/Physic.hpp"

#include "../lib/GUI/AnimationRenderer.hpp"

using std::cout;

int main() 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossy Game");
    SetTargetFPS(80);

    Physic::InitPhysic();
    Physic::SetGravity({0, GRAVITY});

    Character c;
    vector<Object> obs;
    AnimationRenderer renderer;
    UserInputHandler inputHandler;

    for (int i = 0; i < SCREEN_WIDTH / TILE_WIDTH; i++) {
        Object o;

        Rectangle rect = Rectangle({
            (float)i * TILE_WIDTH,
            (float)SCREEN_HEIGHT - TILE_WIDTH,
            (float)TILE_WIDTH,
            (float)TILE_WIDTH
        });

        o.SetPosition(
            rect
        );

        Physic::AddCollider(
            o.GetIndex(),
            Collider({
                true,
                (bool)Collider::Type::RECTANGLE,
                rect, // hitbox
                0.0f
            })
        );

        o.SetAnimationCount(1);
        o.AddAnimation(0, TERRAIN_PATH, 1, 2, 32, 32, 1, 1);
        o.SetCurrentAnimation(0);

        obs.push_back(o);
    }

    for (int i = 0; i < SCREEN_WIDTH / TILE_WIDTH; i++) {
        if (2 <= i && i <= 8) continue;
        Object o;

        Rectangle rect = Rectangle({
            (float)i * TILE_WIDTH,
            (float)SCREEN_HEIGHT - 2 * TILE_WIDTH,
            (float)TILE_WIDTH,
            (float)TILE_WIDTH
        });

        o.SetPosition(
            rect
        );

        Physic::AddCollider(
            o.GetIndex(),
            Collider({
                true,
                (bool)Collider::Type::RECTANGLE,
                rect, // hitbox
                0.0f
            })
        );

        o.SetAnimationCount(1);
        o.AddAnimation(0, TERRAIN_PATH, 1, 2, 32, 32, 1, 1);
        o.SetCurrentAnimation(0);

        obs.push_back(o);
    }

    while (!WindowShouldClose()) {
        /// Input
        inputHandler.next(c);

        // Update
        Physic::ApplyPhysic(c.GetIndex(), &c.position);

        // Render
        BeginDrawing();
            // Reset
            ClearBackground(Color{150, 255, 102, 255});

            renderer.next(c.GetCurrentAnimation(), c.position);
            for (int i = 0; i < (int)obs.size(); i++) {
                renderer.next(obs[i].GetCurrentAnimation(), obs[i].GetPosition());
            }

        EndDrawing();
    }

    CloseWindow();
    Physic::DeInitPhysic();
    
    cout << "Game ended here\n";
    return 0;
}
