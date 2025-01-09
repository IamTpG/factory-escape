#include "Factory.hpp"

#include "../models/Config.hpp"
#include "../data-access/RenderableProvider.hpp"
#include "../data-access/AnimationProvider.hpp"

#include "ecs/core/Coordinator.hpp"

#include "ecs/systems/ColliderSystem.hpp"
#include "ecs/systems/PhysicsSystem.hpp"
#include "ecs/systems/RendererSystem.hpp"

#include "ecs/components/Collider.hpp"
#include "ecs/components/Gravity.hpp"
#include "ecs/components/Renderable.hpp"
#include "ecs/components/RigidBody.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Draggable.hpp"
#include "ecs/components/Animation.hpp"

std::string Factory::ToString() const
{
    return "Factory";
}

Factory::Factory()
{
    Coordinator::GetInstance()->Init();

    Coordinator::GetInstance()->RegisterComponent<Collider>();
    Coordinator::GetInstance()->RegisterComponent<Gravity>();
    Coordinator::GetInstance()->RegisterComponent<Renderable>();
    Coordinator::GetInstance()->RegisterComponent<RigidBody>();
    Coordinator::GetInstance()->RegisterComponent<Transform2>();
    Coordinator::GetInstance()->RegisterComponent<Draggable>();
    Coordinator::GetInstance()->RegisterComponent<Animation>();
}

std::shared_ptr<Factory> Factory::GetInstance()
{
    if (_instance == nullptr) {
        _instance = std::shared_ptr<Factory>(new Factory());
    }
    return _instance;
}

std::shared_ptr<System> Factory::CreateColliderSystem()
{
    std::shared_ptr<System> system = Coordinator::GetInstance()->RegisterSystem<ColliderSystem>();
    
    Signature signature;
    signature.set(Coordinator::GetInstance()->GetComponentType<Transform2>());
    signature.set(Coordinator::GetInstance()->GetComponentType<Collider>());
    Coordinator::GetInstance()->SetSystemSignature<ColliderSystem>(signature);

    return system;
}

std::shared_ptr<System> Factory::CreatePhysicsSystem()
{
    std::shared_ptr<System> system = Coordinator::GetInstance()->RegisterSystem<PhysicsSystem>();

    Signature signature;
    signature.set(Coordinator::GetInstance()->GetComponentType<Transform2>());
    signature.set(Coordinator::GetInstance()->GetComponentType<RigidBody>());
    signature.set(Coordinator::GetInstance()->GetComponentType<Collider>());
    signature.set(Coordinator::GetInstance()->GetComponentType<Gravity>());
    Coordinator::GetInstance()->SetSystemSignature<PhysicsSystem>(signature);

    return system;
}

std::shared_ptr<System> Factory::CreateRendererSystem()
{
    std::shared_ptr<System> system = Coordinator::GetInstance()->RegisterSystem<RendererSystem>();

    Signature signature;
    signature.set(Coordinator::GetInstance()->GetComponentType<Transform2>());
    signature.set(Coordinator::GetInstance()->GetComponentType<Renderable>());
    Coordinator::GetInstance()->SetSystemSignature<RendererSystem>(signature);   

    return system;
}

Entity Factory::CreateCharacter(Vector2 pPosition)
{
    RenderableProvider renderableProvider;
    AnimationProvider animationProvider;

    Renderable renderable = renderableProvider.next(CHARACTER_PATH, Rectangle{0, 0, 16, 16});
    Animation animation = animationProvider.next(CHARACTER_ANIMATION_PATH);

    Transform2 transform = Transform2 {
        .position   = Vector2{(float)SCREEN_OFFSET + pPosition.x * TILE_SIZE, (float)SCREEN_OFFSET + pPosition.y * TILE_SIZE},
        .scale      = Vector2{(float)TILE_SIZE / renderable.rect.width, (float)TILE_SIZE / renderable.rect.height},
        .rotation   = 0.0f
    };

    Collider collider = Collider {
        .boundary = Rectangle{
            .x = transform.position.x,
            .y = transform.position.y,
            .width  = TILE_SIZE,
            .height = TILE_SIZE
        }
    };

    RigidBody rigidBody = RigidBody {
        .acceleration = Vector2{0.0f, 0.0f},
        .velocity     = Vector2{0.0f, 0.0f}
    };

    Gravity gravity = Gravity {
        .acceleration = Vector2{0.0f, GRAVITY}
    };

    Entity character = Coordinator::GetInstance()->CreateEntity();

    Coordinator::GetInstance()->AddComponent<Transform2>(character, transform);
    Coordinator::GetInstance()->AddComponent<Collider>  (character, collider);
    Coordinator::GetInstance()->AddComponent<RigidBody> (character, rigidBody);
    Coordinator::GetInstance()->AddComponent<Gravity>   (character, gravity);
    Coordinator::GetInstance()->AddComponent<Renderable>(character, renderable);
    Coordinator::GetInstance()->AddComponent<Animation> (character, animation);

    return character;
}

Entity Factory::CreateDecorativeTile(Vector2 pPosition, int pId)
{
    RenderableProvider provider;
    Renderable renderable = provider.next(FACTORY_PATH, Rectangle{(float)(pId / 10) * 16, (float)(pId % 10) * 16, 16, 16});

    Transform2 transform = Transform2 {
        .position   = Vector2{(float)SCREEN_OFFSET + pPosition.x * TILE_SIZE, (float)SCREEN_OFFSET + pPosition.y * TILE_SIZE},
        .scale      = Vector2{(float)TILE_SIZE / renderable.rect.width, (float)TILE_SIZE / renderable.rect.height},
        .rotation   = 0.0f
    };

    Entity tile = Coordinator::GetInstance()->CreateEntity();

    Coordinator::GetInstance()->AddComponent<Transform2>(tile, transform);
    Coordinator::GetInstance()->AddComponent<Renderable>(tile, renderable);

    return tile;
}

Entity Factory::CreateSolidTile(Vector2 pPosition, int pId)
{
    Entity tile = CreateDecorativeTile(pPosition, pId);

    Transform2 &transform = Coordinator::GetInstance()->GetComponent<Transform2>(tile);

    Collider collider = Collider {
        .boundary = Rectangle{
            .x = transform.position.x,
            .y = transform.position.y,
            .width  = TILE_SIZE,
            .height = TILE_SIZE
        }
    };

    Coordinator::GetInstance()->AddComponent<Collider>(tile, collider);

    return tile;
}


Entity Factory::CreateDraggableTile(Vector2 pPosition, int pId)
{
    Entity tile = CreateSolidTile(pPosition, pId);
    Coordinator::GetInstance()->AddComponent<Draggable>(tile, Draggable{.dragging = false});
    return tile;
}
