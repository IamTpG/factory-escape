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
    static int getObjectCount();
    static void addObjectCount();
    
    static void initPhysic();
    static void deInitPhysic();
    static void setPhysic(Physic settings);
    static void setGravity(Vector2 force);
    static void addCollider(int index, Collider collider);
    static void addRigidbody(int index, Rigidbody rigidbody);
    static void applyPhysic(int index, Rectangle* position);
    static void setRigidbodyEnabled(int index, bool state);
    static void setRigidbodyVelocity(int index, Vector2 velocity);
    static void addRigidbodyForce(int index, Vector2 force);
    static void setColliderEnabled(int index, bool state);
    static Collider collider(int index);
    static Rigidbody rigidbody(int index);
};

#endif // PHYSIC_HPP
