#include "RendererSystem.hpp"

#include <raylib.h>

#include "../Core/Coordinator.hpp"

#include "../Components/Renderable.hpp"
#include "../Components/Animation.hpp"
#include "../Components/Transform.hpp"

#include "../../../user-interface/TextureRenderer.hpp"
#include "../../../user-interface/AnimationRenderer.hpp"

std::string RendererSystem::ToString() const
{
    return "RendererSystem";
}

void RendererSystem::Update(float deltaTime)
{
    TextureRenderer textureRenderer;
    AnimationRenderer animationRenderer;

    ComponentType animationType = Coordinator::GetInstance()->GetComponentType<Animation>(); 

    for (const auto &entity : entities) {
        const Renderable &renderable = Coordinator::GetInstance()->GetComponent<Renderable>(entity);
        const Transform2 &transform  = Coordinator::GetInstance()->GetComponent<Transform2>(entity);

        Signature entitySignature = Coordinator::GetInstance()->GetEntitySignature(entity);

        if (entitySignature.test(animationType) == true) {
            const Animation &animation = Coordinator::GetInstance()->GetComponent<Animation>(entity);
            animationRenderer.render(renderable, animation, transform);
            continue;
        }
    
        textureRenderer.render(renderable, transform);
    }
}
