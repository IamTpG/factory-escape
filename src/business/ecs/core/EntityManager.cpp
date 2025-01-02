#include "EntityManager.hpp"

std::string EntityManager::ToString() const
{
    return "EntityManager";
}

EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        _availableEntities.push(entity);
    }
}

Entity EntityManager::CreateEntity()
{
    assert(_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    Entity id = _availableEntities.front();
    _availableEntities.pop();
    ++_livingEntityCount;

    return id;
}

void EntityManager::DestroyEntity(Entity pEntity)
{
    assert(pEntity < MAX_ENTITIES && "Entity out of range.");

    _signatures[pEntity].reset();
    _availableEntities.push(pEntity);
    --_livingEntityCount;
}

void EntityManager::SetSignature(Entity pEntity, Signature pSignature)
{
    assert(pEntity < MAX_ENTITIES && "Entity out of range.");

    _signatures[pEntity] = pSignature;
}

Signature EntityManager::GetSignature(Entity pEntity)
{
    assert(pEntity < MAX_ENTITIES && "Entity out of range.");

    return _signatures[pEntity];
}