#ifndef _COORDINATOR_HPP_
#define _COORDINATOR_HPP_

#include <memory>

#include "../../../models/Object.hpp"
#include "ECSTypes.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
// #include "EventManager.hpp"

/// @brief Class to access methods all the managers
class Coordinator : public Object {
private:
	// Hide constructor for singleton design pattern
	Coordinator() = default;

public:
	virtual std::string ToString() const override;

public:
	void Init();
    static std::shared_ptr<Coordinator> GetInstance();

	// ============================== EntityManager methods ==============================

	/// @brief Register a new id from a new entity
	Entity CreateEntity();

	/// @brief Destroy an entity and set it's id free to use
	void DestroyEntity(Entity pEntity);

	/// @brief Set an entity signature (its components)
	void SetEntitySignature(Entity pEntity, Signature pSignature);

	/// @brief Get an entity signature (its components)
	Signature GetEntitySignature(Entity pEntity);


	
	// ============================== ComponentManager methods ==============================

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


	// ============================== SystemManager methods ==============================

	/// @brief Register a system to use (eg. Physic system)
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	/// @brief Set a system signature (components it needs)
	template<typename T>
	void SetSystemSignature(Signature pSignature);

	/// @brief Get a system signature (components it needs)
	template<typename T>
	Signature GetSystemSignature();
    
	/// @brief Get the "real" system from the typename
	template<typename T>
	std::shared_ptr<System> GetSystem();

    /// @brief Remove/add an entity from/to all the systems when its signature changed
	void EntitySignatureChanged(Entity pEntity, Signature pEntitySignature);
	
	
	// Event methods (may use outside classes to handle events)
	// void AddEventListener(EventId eventId, std::function<void(Event&)> const& listener)
	// {
	// 	_eventManager->AddListener(eventId, listener);
	// }

	// void SendEvent(Event& event)
	// {
	// 	_eventManager->SendEvent(event);
	// }

	// void SendEvent(EventId eventId)
	// {
	// 	_eventManager->SendEvent(eventId);
	// }

private:
    inline static std::shared_ptr<Coordinator> _instance = nullptr;
	
	std::shared_ptr<EntityManager>      _entityManager;
	std::shared_ptr<ComponentManager>   _componentManager;
	std::shared_ptr<SystemManager>      _systemManager;
	// std::shared_ptr<EventManager>       _eventManager;
};

// Component methods
template<typename T>
void Coordinator::RegisterComponent()
{
    _componentManager->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity pEntity, T pComponent)
{
    _componentManager->AddComponent<T>(pEntity, pComponent);

    auto signature = _entityManager->GetSignature(pEntity);
    signature.set(_componentManager->GetComponentType<T>(), true);
    _entityManager->SetSignature(pEntity, signature);

    _systemManager->EntitySignatureChanged(pEntity, signature);
}

template<typename T>
void Coordinator::RemoveComponent(Entity pEntity)
{
    _componentManager->RemoveComponent<T>(pEntity);

    auto signature = _entityManager->GetSignature(pEntity);
    signature.set(_componentManager->GetComponentType<T>(), false);
    _entityManager->SetSignature(pEntity, signature);

    _systemManager->EntitySignatureChanged(pEntity, signature);
}

template<typename T>
T& Coordinator::GetComponent(Entity pEntity)
{
    return _componentManager->GetComponent<T>(pEntity);
}

template<typename T>
ComponentType Coordinator::GetComponentType()
{
    return _componentManager->GetComponentType<T>();
}


// System methods
template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
    return _systemManager->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature pSignature)
{
    _systemManager->SetSignature<T>(pSignature);
}

template<typename T>
Signature Coordinator::GetSystemSignature()
{
    return _systemManager->GetSignature<T>();
}

template<typename T>
std::shared_ptr<System> Coordinator::GetSystem()
{
	return _systemManager->GetSystem<T>();
}

#endif // _COORDINATOR_HPP_
