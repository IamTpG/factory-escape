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
    float deltaAccelerationX = 0.0f, deltaAccelerationY = 0.0f;

    for (const auto &entity : entities) {
		auto const &gravity = Coordinator::GetInstance()->GetComponent<Gravity>(entity);
		
        auto &transform = Coordinator::GetInstance()->GetComponent<Transform2>(entity);
        auto &rigidBody = Coordinator::GetInstance()->GetComponent<RigidBody>(entity);
		auto &collider  = Coordinator::GetInstance()->GetComponent<Collider>(entity);

		// transform.position += gravity.acceleration * deltaTime;
		// rigidBody.velocity += gravity.acceleration * deltaTime;

        deltaAccelerationX = (rigidBody.acceleration.x) * deltaTime;
        
		rigidBody.velocity.x += deltaAccelerationX;
		transform.position.x += rigidBody.velocity.x;
		collider.boundary.x  += rigidBody.velocity.x;
    
        offset = colliderSystem->CollideWithOther(entity);
        
        if (Vector2Equals(offset, Vector2Zero()) == false) {
            transform.position.x += offset.x;
            collider.boundary.x  += offset.x;
            rigidBody.velocity.x  = 0.0f;
        }

        deltaAccelerationY = (rigidBody.acceleration.y + gravity.acceleration.y) * deltaTime;
        
		rigidBody.velocity.y += deltaAccelerationY;
		transform.position.y += rigidBody.velocity.y;
		collider.boundary.y  += rigidBody.velocity.y;
            
        offset = colliderSystem->CollideWithOther(entity);

        if (Vector2Equals(offset, Vector2Zero()) == false) {
            transform.position.y += offset.y;
            collider.boundary.y  += offset.y;
            rigidBody.velocity.y  = 0.0f;
        }
    }
}