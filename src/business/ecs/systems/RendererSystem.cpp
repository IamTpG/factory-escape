#include "RendererSystem.hpp"

#include <raylib.h>

#include "../Core/Coordinator.hpp"

#include "../Components/Renderable.hpp"
#include "../Components/Transform.hpp"

#include "../../../user-interface/TextureRenderer.hpp"

std::string RendererSystem::ToString() const
{
    return "RendererSystem";
}

void RendererSystem::Update(float deltaTime)
{
    TextureRenderer textureRenderer;

    for (const auto &entity : entities) {
        Renderable &renderable = Coordinator::GetInstance()->GetComponent<Renderable>(entity);
        Transform2 &transform  = Coordinator::GetInstance()->GetComponent<Transform2>(entity);

        textureRenderer.render(renderable, transform);
    }
}
