#include "ComponentManager.hpp"

std::string ComponentManager::ToString() const
{
    return "ComponentManager";
}

void ComponentManager::EntityDestroyed(Entity pEntity)
{
    for (auto const& pair : _componentArrays) {
        auto const& component = pair.second;
        component->EntityDestroyed(pEntity);
    }
}
