#include "RendererSystem.hpp"

#include <raylib.h>
#include <raymath.h>

#include "../Core/Coordinator.hpp"

#include "../Components/Renderable.hpp"
#include "../Components/Transform.hpp"

std::string RendererSystem::ToString() const
{
    return "RendererSystem";
}

void RendererSystem::Update(float deltaTime)
{
    for (const auto &entity : entities) {
        Renderable &renderable = Coordinator::GetInstance()->GetComponent<Renderable>(entity);
        Transform2 &transform  = Coordinator::GetInstance()->GetComponent<Transform2>(entity);
        
        Rectangle source = renderable.rect;

        Rectangle dest = Rectangle {
            .x      = transform.position.x,
            .y      = transform.position.y,
            .width  = renderable.rect.width  * transform.scale.x,
            .height = renderable.rect.height * transform.scale.y
        };

        DrawTexturePro(renderable.texture, source, dest, Vector2Zero(), transform.rotation, WHITE);

        // no scale, no rotation
        // DrawTextureV(renderable.texture, transform.position, WHITE);
    }
}
