#ifndef _COMPONENT_ARRAY_HPP_
#define _COMPONENT_ARRAY_HPP_

#include <array>
#include <cassert>
#include <unordered_map>
#include <typeinfo>

#include "../../../models/Object.hpp"
#include "ECSTypes.hpp"

/// @brief Interface class for Component Array class
class IComponentArray : public Object {
public:
	/// @brief Remove an entity's component when it's destroyed
	virtual void EntityDestroyed(Entity entity) = 0;
};

/// @brief Class to manage entity's components
/// @tparam T Component type
template<typename T>
class ComponentArray : public IComponentArray {
public:
    virtual std::string ToString() const override;

public:
	virtual void EntityDestroyed(Entity pEntity) override;

	/// @brief Add a component to an entity
	void InsertData(Entity pEntity, T pComponent);

	/// @brief Remove a component from an entity
	void RemoveData(Entity entity);

	/// @brief Get component data
	T& GetData(Entity pEntity);

private:
	std::array<T, MAX_ENTITIES> _componentArray{};
	std::unordered_map<Entity, size_t> _entityToIndexMap{};
	std::unordered_map<size_t, Entity> _indexToEntityMap{};
	size_t _size{};
};

template<typename T>
std::string ComponentArray<T>::ToString() const
{
	return "ComponentArray<" + std::string(typeid(T).name()) + ">";
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity pEntity)
{
	if (_entityToIndexMap.find(pEntity) != _entityToIndexMap.end()) {
		RemoveData(pEntity);
	}
}

template<typename T>
void ComponentArray<T>::InsertData(Entity pEntity, T pComponent)
{
	assert(_entityToIndexMap.find(pEntity) == _entityToIndexMap.end() && "Component added to same entity more than once.");

	// Put new entry at end
	size_t newIndex = _size;
	_entityToIndexMap[pEntity] = newIndex;
	_indexToEntityMap[newIndex] = pEntity;
	_componentArray[newIndex] = pComponent;
	++_size;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity)
{
	assert(_entityToIndexMap.find(entity) != _entityToIndexMap.end() && "Removing non-existent component.");

	// Copy element at end into deleted element's place to maintain density
	size_t indexOfRemovedEntity = _entityToIndexMap[entity];
	size_t indexOfLastElement = _size - 1;
	_componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

	// Update map to point to moved spot
	Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
	_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

	_entityToIndexMap.erase(entity);
	_indexToEntityMap.erase(indexOfLastElement);

	--_size;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity pEntity)
{
	assert(_entityToIndexMap.find(pEntity) != _entityToIndexMap.end() && "Retrieving non-existent component.");

	return _componentArray[_entityToIndexMap[pEntity]];
}

#endif // _COMPONENT_ARRAY_HPP_
