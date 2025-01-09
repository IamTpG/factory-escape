#ifndef _COMPONENT_MANAGER_HPP_
#define _COMPONENT_MANAGER_HPP_

#include <any>
#include <memory>
#include <unordered_map>

#include "../../../models/Object.hpp"
#include "ECSTypes.hpp"
#include "ComponentArray.hpp"

/// @brief Class to manage components
class ComponentManager : public Object {    
public:
	virtual std::string ToString() const override;

public:
	/// @brief Register a component type
	template<typename T>
	void RegisterComponent();

	/// @brief Get component id from the "real" type
	template<typename T>
	ComponentType GetComponentType();

	/// @brief Add a component to an entity
	template<typename T>
	void AddComponent(Entity pEntity, T pComponent);

	/// @brief Remove a component from an entity
	template<typename T>
	void RemoveComponent(Entity pEntity);

	/// @brief Get a component's data from an entity
	template<typename T>
	T& GetComponent(Entity pEntity);

	/// @brief Remove a component from an entity when it's destroyed
	void EntityDestroyed(Entity pEntity);

private:
	/// @brief Get the array of a component type
	template<typename T>
	std::shared_ptr<ComponentArray<T>> _GetComponentArray();

private:
	std::unordered_map<std::string, ComponentType> _componentTypes{};
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> _componentArrays{};
	ComponentType _nextComponentType{};
};

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::_GetComponentArray()
{
    std::string typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component not registered before use.");

    return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
}

template<typename T>
void ComponentManager::RegisterComponent()
{
    std::string typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) == _componentTypes.end() && "Registering component type more than once.");

    _componentTypes.insert({typeName, _nextComponentType});
    _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    ++_nextComponentType;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
    std::string typeName = typeid(T).name();

    assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component not registered before use.");

    return _componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity pEntity, T pComponent)
{
    _GetComponentArray<T>()->InsertData(pEntity, pComponent);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity pEntity)
{
    _GetComponentArray<T>()->RemoveData(pEntity);
}

template<typename T>
T& ComponentManager::GetComponent(Entity pEntity)
{
    return _GetComponentArray<T>()->GetData(pEntity);
}

#endif // _COMPONENT_MANAGER_HPP_
