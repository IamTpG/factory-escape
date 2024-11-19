#include "Physic.hpp"
#include "../DTO/Define.hpp"

#include <math.h>
#include <stdio.h>

using std::pair;

static Physic       physic              = {true, Vector2{0, 0}};
static Collider*    colliders           = nullptr;
static Rigidbody*   rigidbodies         = nullptr;
static bool         collisionChecker    = false;
static int          objectCount         = 0;

int Physic::GetObjectCount()
{
    return objectCount;
}

void Physic::AddObjectCount()
{
    ++objectCount;
}

void Physic::InitPhysic()
{    
    colliders = new Collider[PHYSIC_MAX_COUNT];
    rigidbodies = new Rigidbody[PHYSIC_MAX_COUNT];

    for (int i = 0; i < PHYSIC_MAX_COUNT; i++) {
        rigidbodies[i].enabled = false;
        rigidbodies[i].mass = 0.0f;
        rigidbodies[i].velocity = (Vector2){0, 0};
        rigidbodies[i].acceleration = (Vector2){0, 0};
        rigidbodies[i].isGrounded = false;
        rigidbodies[i].isContact = false;
        rigidbodies[i].friction = 0.0f;
        
        colliders[i].enabled = false;
        colliders[i].boundary = (Rectangle){0, 0, 0, 0};
        colliders[i].radius = 0.0f;
        colliders[i].type = (bool)Collider::Type::RECTANGLE;
    }
}

void Physic::DeInitPhysic()
{
    delete[] colliders;
    delete[] rigidbodies;
}

void Physic::SetPhysic(Physic pSettings)
{
    physic.enabled = pSettings.enabled;
    physic.gravity = pSettings.gravity;
}

void Physic::SetGravity(Vector2 pGravity)
{
    physic.gravity = pGravity;
}

Collider Physic::GetCollider(int pIndex)
{
    return colliders[pIndex];
}

Rigidbody Physic::GetRigidbody(int pIndex)
{
    return rigidbodies[pIndex];
}

void Physic::AddCollider(int pIndex, Collider pCollider)
{
    colliders[pIndex] = pCollider;
}

void Physic::AddRigidbody(int pIndex, Rigidbody pRigidbody)
{
    rigidbodies[pIndex] = pRigidbody;
}

void Physic::SetColliderEnabled(int pIndex, bool pState)
{
    colliders[pIndex].enabled = pState;
}

void Physic::SetRigidbodyEnabled(int pIndex, bool pState)
{
    rigidbodies[pIndex].enabled = pState;
}

void Physic::SetRigidbodyVelocity(int pIndex, Vector2 pVelocity)
{
    rigidbodies[pIndex].velocity.x = pVelocity.x;
    rigidbodies[pIndex].velocity.y = pVelocity.y;
}

void Physic::SetRigidbodyVelocityX(int pIndex, float pVelocityX)
{
    rigidbodies[pIndex].velocity.x = pVelocityX;
}

void Physic::SetRigidbodyVelocityY(int pIndex, float velocityY)
{
    rigidbodies[pIndex].velocity.y = velocityY;
}

void Physic::AddRigidbodyForce(int pIndex, Vector2 pForce)
{
    rigidbodies[pIndex].acceleration.x = pForce.x * rigidbodies[pIndex].mass;
    rigidbodies[pIndex].acceleration.y = pForce.y * rigidbodies[pIndex].mass;
}

// Helper function
pair<bool, bool> CheckCollisionWithOthers(int pIndex)
{
    if (colliders[pIndex].enabled == false) {
        return {false, false};
    }

    // Check collision with other colliders
    bool collisionChecker = false;
    bool isGrounded = false;    

    if (colliders[pIndex].enabled) {
        for (int j = 0; j < PHYSIC_MAX_COUNT; j++) {
            if (pIndex == j) {
                continue;
            }

            if (colliders[j].enabled) {
                if (colliders[pIndex].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::RECTANGLE) {
                    if (CheckCollisionRecs(colliders[pIndex].boundary, colliders[j].boundary)) {
                        collisionChecker = true;
                        
                        // Check if the object is on the ground (only for Y-axis collision)
                        if (colliders[pIndex].boundary.y < colliders[j].boundary.y) {
                            isGrounded = true;
                        }
                    }
                }
                if (colliders[pIndex].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                    if (CheckCollisionCircles((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, (Vector2){colliders[pIndex].boundary.x, colliders[pIndex].boundary.y}, colliders[pIndex].radius)) {
                        collisionChecker = true;

                        // Check if the object is on the ground (only for Y-axis collision)
                        if (colliders[pIndex].boundary.y < colliders[j].boundary.y - colliders[j].radius) {
                            isGrounded = true;
                        }
                    }
                }
                if (colliders[pIndex].type != colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                    if (CheckCollisionCircleRec((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, colliders[pIndex].boundary)) {
                        collisionChecker = true;

                        // Check if the object is on the ground (only for Y-axis collision)
                        if (colliders[pIndex].boundary.y - colliders[pIndex].radius > colliders[j].boundary.y) {
                            isGrounded = true;
                        }
                    }
                }
                if (colliders[pIndex].type != colliders[j].type && colliders[pIndex].type == (bool)Collider::Type::CIRCLE) {
                    if (CheckCollisionCircleRec((Vector2){colliders[pIndex].boundary.x, colliders[pIndex].boundary.y}, colliders[pIndex].radius, colliders[j].boundary)) {
                        collisionChecker = true;

                        // Check if the object is on the ground (only for Y-axis collision)
                        if (colliders[pIndex].boundary.y - colliders[pIndex].radius > colliders[j].boundary.y - colliders[j].radius) {
                            isGrounded = true;
                        }
                    }
                }                    
            }
        }
    }

    return {collisionChecker, isGrounded};
}

// Helper function
void UpdatePositionX(int pIndex, Rectangle* pPosition)
{
    // Update pPosition and collider vector
    pPosition->x += rigidbodies[pIndex].velocity.x;
    colliders[pIndex].boundary.x += rigidbodies[pIndex].velocity.x;
    
    // Check collision with other colliders
    collisionChecker = CheckCollisionWithOthers(pIndex).first;

    // Re-update if there was a collision
    if (collisionChecker && rigidbodies[pIndex].velocity.x != 0) {
        pPosition->x -= rigidbodies[pIndex].velocity.x;
        colliders[pIndex].boundary.x -= rigidbodies[pIndex].velocity.x;
        rigidbodies[pIndex].velocity.x = rigidbodies[pIndex].velocity.x;
    }
}

// Helper function
void UpdatePositionY(int pIndex, Rectangle* pPosition)
{
    // Update pPosition and collider vector
    pPosition->y -= rigidbodies[pIndex].velocity.y;
    colliders[pIndex].boundary.y -= rigidbodies[pIndex].velocity.y;
    
    // Check collision with other colliders
    pair<bool, bool> collisionChecker = CheckCollisionWithOthers(pIndex);

    // Update grounded rigidbody state
    rigidbodies[pIndex].isGrounded = collisionChecker.second;
    
    // Re-update if there was a collision
    if (collisionChecker.first && rigidbodies[pIndex].velocity.y != 0) {
        pPosition->y += rigidbodies[pIndex].velocity.y;
        colliders[pIndex].boundary.y += rigidbodies[pIndex].velocity.y;
        rigidbodies[pIndex].velocity.y = -rigidbodies[pIndex].velocity.y * rigidbodies[pIndex].bounciness;
    }
}

void Physic::ApplyPhysic(int pIndex, Rectangle *pPosition)
{
    if (rigidbodies[pIndex].enabled == false) {
        return;
    }

    // Apply gravity
    rigidbodies[pIndex].velocity.y += rigidbodies[pIndex].acceleration.y;
    rigidbodies[pIndex].velocity.x += rigidbodies[pIndex].acceleration.x;
    
    rigidbodies[pIndex].velocity.y += physic.gravity.y;
    rigidbodies[pIndex].velocity.x += physic.gravity.x;
    
    // Apply friction to velocity
    if (rigidbodies[pIndex].isGrounded) {
        if (rigidbodies[pIndex].velocity.x > DECIMAL_FIX) {
            rigidbodies[pIndex].velocity.x -= rigidbodies[pIndex].friction;
        }
        else if (rigidbodies[pIndex].velocity.x < -DECIMAL_FIX) {
            rigidbodies[pIndex].velocity.x += rigidbodies[pIndex].friction;
        }
        else {
            rigidbodies[pIndex].velocity.x = 0;
        }
    }
    
    // if (rigidbodies[pIndex].velocity.y > DECIMAL_FIX) {
    //     rigidbodies[pIndex].velocity.y -= rigidbodies[pIndex].friction;
    // }
    // else if (rigidbodies[pIndex].velocity.y < -DECIMAL_FIX) {
    //     rigidbodies[pIndex].velocity.y += rigidbodies[pIndex].friction;
    // }
    // else {
    //     rigidbodies[pIndex].velocity.y = 0;
    // }
    
    // Apply friction to acceleration
    if (rigidbodies[pIndex].isGrounded) {
        if (rigidbodies[pIndex].acceleration.x > DECIMAL_FIX) {
            rigidbodies[pIndex].acceleration.x -= rigidbodies[pIndex].friction;
        }
        else if (rigidbodies[pIndex].acceleration.x < -DECIMAL_FIX) {
            rigidbodies[pIndex].acceleration.x += rigidbodies[pIndex].friction;
        }
        else {
            rigidbodies[pIndex].acceleration.x = 0;
        }
    }
    
    // if (rigidbodies[pIndex].acceleration.y > DECIMAL_FIX) {
    //     rigidbodies[pIndex].acceleration.y -= rigidbodies[pIndex].friction;
    // }
    // else if (rigidbodies[pIndex].acceleration.y < -DECIMAL_FIX) {
    //     rigidbodies[pIndex].acceleration.y += rigidbodies[pIndex].friction;
    // }
    // else {
    //     rigidbodies[pIndex].acceleration.y = 0;
    // }

    UpdatePositionX(pIndex, pPosition);
    UpdatePositionY(pIndex, pPosition);
}
