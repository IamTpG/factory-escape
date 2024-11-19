#include <iostream>
#include <raylib.h>

#include "../lib/DTO/Define.hpp"
#include "../lib/DTO/Character.hpp"
#include "../lib/GUI/AnimationRenderer.hpp"
#include "../lib/DTO/Animation.hpp"

#include "../lib/BUS/Physic.hpp"

using std::cout;

int main() 
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossy Game");
    SetTargetFPS(80);

    Physic::initPhysic();
    Physic::setGravity({0, GRAVITY});

    Character c;
    vector<Object> obs;

    #define TILE_WIDTH 64

    for (int i = 0; i < SCREEN_WIDTH / TILE_WIDTH; i++) {
        Object o;

        Rectangle rect = Rectangle({
            (float)i * TILE_WIDTH,
            (float)SCREEN_HEIGHT - TILE_WIDTH,
            (float)TILE_WIDTH,
            (float)TILE_WIDTH
        });

        o.setPosition(
            rect
        );

        Physic::addCollider(
            o.index(),
            Collider({
                true,
                (bool)Collider::Type::RECTANGLE,
                rect, // hitbox
                0.0f
            })
        );

        o.setAnimationCount(1);
        o.addAnimation(0, TERRAIN_PATH, 1, 2, 32, 32, 1, 1);
        o.setAnimation(0);

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

        o.setPosition(
            rect
        );

        Physic::addCollider(
            o.index(),
            Collider({
                true,
                (bool)Collider::Type::RECTANGLE,
                rect, // hitbox
                0.0f
            })
        );

        o.setAnimationCount(1);
        o.addAnimation(0, TERRAIN_PATH, 1, 2, 32, 32, 1, 1);
        o.setAnimation(0);

        obs.push_back(o);
    }

    AnimationRenderer renderer;

    while (!WindowShouldClose()) {
        
        /// Input
        if (IsKeyDown(KEY_RIGHT)) {
            Physic::setRigidbodyVelocityX(c.index(), CHARACTER_SPEED_X);
            c.setAnimation((int)Animation::Character::WALK_RIGHT);
        }
        if (IsKeyDown(KEY_LEFT)) {
            Physic::setRigidbodyVelocityX(c.index(), -CHARACTER_SPEED_X);
            c.setAnimation((int)Animation::Character::WALK_LEFT);
        }
        if (IsKeyDown(KEY_UP) && Physic::rigidbody(c.index()).isGrounded) {
            Physic::setRigidbodyVelocityY(c.index(), CHARACTER_SPEED_Y);
        }

        // Update
        Physic::applyPhysic(c.index(), &c._position);

        if (Physic::rigidbody(c.index()).velocity.x == 0 &&
            Physic::rigidbody(c.index()).velocity.y == 0) {
            if (c.currentAnimation() == (int)Animation::Character::WALK_RIGHT) {
                c.setAnimation((int)Animation::Character::IDLE_RIGHT);
            }
            else if (c.currentAnimation() == (int)Animation::Character::WALK_LEFT) {
                c.setAnimation((int)Animation::Character::IDLE_LEFT);
            }
        }

        // Render
        BeginDrawing();
            // Reset
            ClearBackground(Color{150, 255, 102, 255});
            
            renderer.next(c.animation(), c.position());
            for (int i = 0; i < (int)obs.size(); i++) {
                renderer.next(obs[i].animation(), obs[i].position());
            }
        EndDrawing();
    }

    CloseWindow();
    Physic::deInitPhysic();
    cout << "Game ended\n";
    return 0;
}
