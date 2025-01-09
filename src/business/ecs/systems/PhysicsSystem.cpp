#include "PhysicsSystem.hpp"

#include <raylib.h>
#include <raymath.h>

#include "../Core/Coordinator.hpp"

#include "../Components/Transform.hpp"
#include "../Components/RigidBody.hpp"
#include "../Components/Collider.hpp"
#include "../Components/Gravity.hpp"

#include "ColliderSystem.hpp"

std::string PhysicsSystem::ToString() const
{
    return "PhysicsSystem";
}

void PhysicsSystem::Update(float deltaTime)
{
    std::shared_ptr<ColliderSystem> colliderSystem = std::dynamic_pointer_cast<ColliderSystem>(Coordinator::GetInstance()->GetSystem<ColliderSystem>());
    Vector2 offset = Vector2Zero();
    float accelerationX = 0.0f, accelerationY = 0.0f;

    for (const auto &entity : entities) {
		const auto &gravity = Coordinator::GetInstance()->GetComponent<Gravity>(entity);
		
        auto &transform = Coordinator::GetInstance()->GetComponent<Transform2>(entity);
        auto &rigidBody = Coordinator::GetInstance()->GetComponent<RigidBody>(entity);
		auto &collider  = Coordinator::GetInstance()->GetComponent<Collider>(entity);

        // x = x_0 + (v_0 * t) + (0.5 * a * t^2)
        // v = v_0 + (a * t)
        accelerationX = rigidBody.acceleration.x;
		transform.position.x += (rigidBody.velocity.x * deltaTime) + (0.5f * accelerationX * deltaTime * deltaTime);
		rigidBody.velocity.x += (accelerationX * deltaTime);
        
        offset = colliderSystem->CollideWithOther(entity);
        
        if (Vector2Equals(offset, Vector2Zero()) == false) {
            transform.position.x += offset.x;
            collider.boundary.x  += offset.x;
            rigidBody.velocity.x  = 0.0f;
        }

        // x = x_0 + (v_0 * t) + (0.5 * a * t^2)
        // v = v_0 + (a * t)
        accelerationY = rigidBody.acceleration.y + gravity.acceleration.y;
		transform.position.y += (rigidBody.velocity.y * deltaTime) + (0.5f * accelerationX * deltaTime * deltaTime);
		rigidBody.velocity.y += (accelerationY * deltaTime);
                    
        offset = colliderSystem->CollideWithOther(entity);

        if (Vector2Equals(offset, Vector2Zero()) == false) {
            transform.position.y += offset.y;
            collider.boundary.y  += offset.y;
            rigidBody.velocity.y  = 0.0f;
        }
    }
}