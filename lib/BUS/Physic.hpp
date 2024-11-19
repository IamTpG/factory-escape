#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <raylib.h>
#include <vector>

using std::vector;

class Transform2 {
public:
    Vector2 position;
    float rotation;
    Vector2 scale;
};

class Collider {
public:
    enum class Type {
        RECTANGLE = 0,
        CIRCLE    = 1,
    };
public:
    bool enabled;
    bool type;
    Rectangle boundary;
    float radius;
};

class Rigidbody {
public:
    bool enabled;
    float mass;
    Vector2 acceleration;
    Vector2 velocity;
    bool isGrounded;
    bool isContact;
    bool applyGravity;
    float friction;
    float bounciness;
};

class Physic {
public:
    bool enabled;
    Vector2 gravity;
public:
    static int GetObjectCount();
    static void AddObjectCount();
    
    static void InitPhysic();
    static void DeInitPhysic();

    static void SetPhysic(Physic pSettings);
    static void SetGravity(Vector2 pGravity);
    
    static Collider GetCollider(int pIndex);
    static Rigidbody GetRigidbody(int pIndex);
    
    static void AddCollider(int pIndex, Collider pCollider);
    static void AddRigidbody(int pIndex, Rigidbody pRigidbody);
    
    static void SetColliderEnabled(int pIndex, bool pState);
    static void SetRigidbodyEnabled(int pIndex, bool pState);
    static void SetRigidbodyVelocity(int pIndex, Vector2 pVelocity);
    static void SetRigidbodyVelocityX(int pIndex, float pVelocityX);
    static void SetRigidbodyVelocityY(int pIndex, float pVelocityY);
    static void AddRigidbodyForce(int pIndex, Vector2 pForce);
    
    static void ApplyPhysic(int pIndex, Rectangle* pPosition);
};

#endif // PHYSIC_HPP
