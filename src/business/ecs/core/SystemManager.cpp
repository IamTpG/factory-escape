#include "SystemManager.hpp"

std::string SystemManager::ToString() const
{
    return "SystemManager";
}

void SystemManager::EntityDestroyed(Entity pEntity)
{
    for (auto const &pair : _systems) {
        auto const &system = pair.second;
        system->entities.erase(pEntity);
    }
}

void SystemManager::EntitySignatureChanged(Entity pEntity, Signature pEntitySignature)
{
    for (auto const &pair : _systems) {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemSignature = _signatures[type];

        if ((pEntitySignature & systemSignature) == systemSignature) {
            system->entities.insert(pEntity);
        }
        else {
            system->entities.erase(pEntity);
        }
    }
}
