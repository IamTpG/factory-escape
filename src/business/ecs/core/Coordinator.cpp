#include "Coordinator.hpp"

std::string Coordinator::ToString() const
{
    return "Coordinator";
}

void Coordinator::Init()
{
    _entityManager      = std::make_shared<EntityManager>();
    _componentManager   = std::make_shared<ComponentManager>();
    _systemManager      = std::make_shared<SystemManager>();
    // _eventManager       = std::make_shared<EventManager>();
}

std::shared_ptr<Coordinator> Coordinator::GetInstance()
{
    if (_instance == nullptr) {
		auto temp = new Coordinator();
		_instance = std::shared_ptr<Coordinator>(temp);
    }
    return _instance;
}


// ============================== EntitySystem methods ==============================

Entity Coordinator::CreateEntity()
{
    return _entityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity pEntity)
{
    _entityManager->DestroyEntity(pEntity);
    _componentManager->EntityDestroyed(pEntity);
    _systemManager->EntityDestroyed(pEntity);
}

void Coordinator::SetEntitySignature(Entity pEntity, Signature pSignature)
{
    _entityManager->SetSignature(pEntity, pSignature);
    _systemManager->EntitySignatureChanged(pEntity, pSignature);
}

Signature Coordinator::GetEntitySignature(Entity pEntity)
{
    return _entityManager->GetSignature(pEntity);
}



// ============================== ComponentManager methods ==============================

void Coordinator::EntityDestroyed(Entity pEntity)
{
    _componentManager->EntityDestroyed(pEntity);
    _systemManager->EntityDestroyed(pEntity);
}



// ============================== ComponentManager methods ==============================

void Coordinator::EntitySignatureChanged(Entity pEntity, Signature pEntitySignature)
{
    _systemManager->EntitySignatureChanged(pEntity, pEntitySignature);
}
