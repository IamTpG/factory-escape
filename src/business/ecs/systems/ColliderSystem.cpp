#include "ColliderSystem.hpp"

#include <raymath.h>

#include "../core/Coordinator.hpp"

#include "../components/Collider.hpp"

#include "../../math/Float.hpp"

std::string ColliderSystem::ToString() const
{
    return "ColliderSystem";
}

void ColliderSystem::Update(float deltaTime)
{
    // Do nothing
}

Vector2 ColliderSystem::CollideWithOther(const Entity &pEntity)
{
    // If the pEntity is not in the system, there is no collision.
    if (entities.find(pEntity) == entities.end()) {
        return Vector2Zero();
    }

    Collider &a = Coordinator::GetInstance()->GetComponent<Collider>(pEntity);
    float ax1 = a.boundary.x;
    float ax2 = a.boundary.x + a.boundary.width;
    float ay1 = a.boundary.y;
    float ay2 = a.boundary.y + a.boundary.height;

    Vector2 offset = Vector2Zero();

    for (const auto &entity : entities) {
        if (entity == pEntity) {
            continue;
        }

        Collider &b = Coordinator::GetInstance()->GetComponent<Collider>(entity);
        float bx1 = b.boundary.x;
        float bx2 = b.boundary.x + b.boundary.width;
        float by1 = b.boundary.y;
        float by2 = b.boundary.y + b.boundary.height;

        if (FloatGreaterThan(ax1, bx2) || FloatLessThan(ax2, bx1)) {
            continue;
        }

        if (FloatGreaterThan(ay1, by2) || FloatLessThan(ay2, by1)) {
            continue;
        }

        if (FloatLessThanOrEquals(bx1, ax1) && FloatLessThanOrEquals(ax1, bx2)) {
            offset.x = bx2 - ax1;
        }

        if (FloatLessThanOrEquals(bx1, ax2) && FloatLessThanOrEquals(ax2, bx2)) {
            offset.x = bx1 - ax2;
        }

        if (FloatLessThanOrEquals(by1, ay1) && FloatLessThanOrEquals(ay1, by2)) {
            offset.y = by2 - ay1;
        }

        if (FloatLessThanOrEquals(by1, ay2) && FloatLessThanOrEquals(ay2, by2)) {
            offset.y = by1 - ay2;
        }


        if (FloatEquals(offset.x, 0.0f) == false && FloatEquals(offset.y, 0.0f) == false) {
            printf("Entity #%d collides with Entity #%d\n", pEntity, entity);

            return offset;
        }
    }

    return Vector2Zero();
}
