#include "Physic.hpp"
#include "../DTO/Define.hpp"

#include <math.h>
#include <stdio.h>

static Physic       physic              = {true, Vector2{0, 0}};
static Collider*    colliders           = nullptr;
static Rigidbody*   rigidbodies         = nullptr;
static bool         collisionChecker    = false;
static int          objectCount         = 0;

int Physic::getObjectCount()
{
    return objectCount;
}

void Physic::addObjectCount()
{
    ++objectCount;
}

void Physic::initPhysic()
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

void Physic::deInitPhysic()
{
    delete[] colliders;
    delete[] rigidbodies;
}

void Physic::setPhysic(Physic settings)
{
    physic.enabled = settings.enabled;
    physic.gravity = settings.gravity;
}

void Physic::setGravity(Vector2 force)
{
    physic.gravity = force;
}

void Physic::addCollider(int index, Collider collider)
{
    colliders[index] = collider;
}

void Physic::addRigidbody(int index, Rigidbody rigidbody)
{
    rigidbodies[index] = rigidbody;
}

void Physic::applyPhysic(int index, Rectangle *position)
{
    if (rigidbodies[index].enabled) {
        // Apply gravity
        rigidbodies[index].velocity.y += rigidbodies[index].acceleration.y;
        rigidbodies[index].velocity.x += rigidbodies[index].acceleration.x;
        
        rigidbodies[index].velocity.y += physic.gravity.y;
        rigidbodies[index].velocity.x += physic.gravity.x;
        
        // Apply friction to velocity
        if (rigidbodies[index].isGrounded) {
            if (rigidbodies[index].velocity.x > DECIMAL_FIX) {
                rigidbodies[index].velocity.x -= rigidbodies[index].friction;
            }
            else if (rigidbodies[index].velocity.x < -DECIMAL_FIX) {
                rigidbodies[index].velocity.x += rigidbodies[index].friction;
            }
            else {
                rigidbodies[index].velocity.x = 0;
            }
        }
        
        // if (rigidbodies[index].velocity.y > DECIMAL_FIX) {
        //     rigidbodies[index].velocity.y -= rigidbodies[index].friction;
        // }
        // else if (rigidbodies[index].velocity.y < -DECIMAL_FIX) {
        //     rigidbodies[index].velocity.y += rigidbodies[index].friction;
        // }
        // else {
        //     rigidbodies[index].velocity.y = 0;
        // }
        
        // Apply friction to acceleration
        if (rigidbodies[index].isGrounded) {
            if (rigidbodies[index].acceleration.x > DECIMAL_FIX) {
                rigidbodies[index].acceleration.x -= rigidbodies[index].friction;
            }
            else if (rigidbodies[index].acceleration.x < -DECIMAL_FIX) {
                rigidbodies[index].acceleration.x += rigidbodies[index].friction;
            }
            else {
                rigidbodies[index].acceleration.x = 0;
            }
        }
        
        // if (rigidbodies[index].acceleration.y > DECIMAL_FIX) {
        //     rigidbodies[index].acceleration.y -= rigidbodies[index].friction;
        // }
        // else if (rigidbodies[index].acceleration.y < -DECIMAL_FIX) {
        //     rigidbodies[index].acceleration.y += rigidbodies[index].friction;
        // }
        // else {
        //     rigidbodies[index].acceleration.y = 0;
        // }

        
        // Update position vector
        position->x += rigidbodies[index].velocity.x;
        position->y -= rigidbodies[index].velocity.y;
        
        // Update collider boundary
        colliders[index].boundary.x += rigidbodies[index].velocity.x;
        colliders[index].boundary.y -= rigidbodies[index].velocity.y;
        
        // Check collision with other colliders
        collisionChecker = false;
        rigidbodies[index].isContact = false;

        if (colliders[index].enabled) {
            for (int j = 0; j < PHYSIC_MAX_COUNT; j++) {
                if (index == j) continue;
                
                if (colliders[j].enabled) {
                    if (colliders[index].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::RECTANGLE) {
                        if (CheckCollisionRecs(colliders[index].boundary, colliders[j].boundary)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircles((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, (Vector2){colliders[index].boundary.x, colliders[index].boundary.y}, colliders[index].radius)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type != colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircleRec((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, colliders[index].boundary)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type != colliders[j].type && colliders[index].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircleRec((Vector2){colliders[index].boundary.x, colliders[index].boundary.y}, colliders[index].radius, colliders[j].boundary)) {
                            collisionChecker = true;
                        }
                    }                    
                }
            }
        }
        
        // Update grounded rigidbody state
        rigidbodies[index].isGrounded = collisionChecker;
        
        // Set grounded state if needed (fix overlap and set y velocity)
        if (collisionChecker && rigidbodies[index].velocity.y != 0) {
            position->y += rigidbodies[index].velocity.y;
            colliders[index].boundary.y += rigidbodies[index].velocity.y;
            rigidbodies[index].velocity.y = -rigidbodies[index].velocity.y * rigidbodies[index].bounciness;
        }
        
        collisionChecker = false;

        if (colliders[index].enabled) {
            for (int j = 0; j < PHYSIC_MAX_COUNT; j++) {
                if (index == j) continue;
                

                if (colliders[j].enabled) {
                    if (colliders[index].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::RECTANGLE) {
                        if (CheckCollisionRecs(colliders[index].boundary, colliders[j].boundary)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type == colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircles((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, (Vector2){colliders[index].boundary.x, colliders[index].boundary.y}, colliders[index].radius)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type != colliders[j].type && colliders[j].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircleRec((Vector2){colliders[j].boundary.x, colliders[j].boundary.y}, colliders[j].radius, colliders[index].boundary)) {
                            collisionChecker = true;
                        }
                    }
                    if (colliders[index].type != colliders[j].type && colliders[index].type == (bool)Collider::Type::CIRCLE) {
                        if (CheckCollisionCircleRec((Vector2){colliders[index].boundary.x, colliders[index].boundary.y}, colliders[index].radius, colliders[j].boundary)) {
                            collisionChecker = true;
                        }
                    }                    
                }

                // if (collisionChecker) {
                //     printf("index[%f, %f, %f, %f] & j[%f, %f, %f, %f]\n",
                //         colliders[index].boundary.x, colliders[index].boundary.y, colliders[index].boundary.width, colliders[index].boundary.height,
                //         colliders[j].boundary.x, colliders[j].boundary.y, colliders[j].boundary.width, colliders[j].boundary.height
                //     );
                // }
            }
        }

        if (collisionChecker && rigidbodies[index].velocity.x != 0) {
            position->x -= rigidbodies[index].velocity.x;
            colliders[index].boundary.x -= rigidbodies[index].velocity.x;
            rigidbodies[index].velocity.x = rigidbodies[index].velocity.x;
        }
    }
}

void Physic::setRigidbodyEnabled(int index, bool state)
{
    rigidbodies[index].enabled = state;
}

void Physic::setRigidbodyVelocity(int index, Vector2 velocity)
{
    rigidbodies[index].velocity.x = velocity.x;
    rigidbodies[index].velocity.y = velocity.y;
}

void Physic::addRigidbodyForce(int index, Vector2 force)
{
    rigidbodies[index].acceleration.x = force.x * rigidbodies[index].mass;
    rigidbodies[index].acceleration.y = force.y * rigidbodies[index].mass;
}

void Physic::setColliderEnabled(int index, bool state)
{
    colliders[index].enabled = state;
}

Collider Physic::collider(int index)
{
    return colliders[index];
}

Rigidbody Physic::rigidbody(int index)
{
    return rigidbodies[index];
}
