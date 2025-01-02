#ifndef _SYSTEM_MANAGER_HPP_
#define _SYSTEM_MANAGER_HPP_

#include <cassert>
#include <memory>
#include <unordered_map>

#include "../../../models/Object.hpp"
#include "System.hpp"
#include "ECSTypes.hpp"

class SystemManager : public Object {
public:
	std::string ToString() const override;

public:
	/// @brief Register a system to use (eg. Physic system)
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	/// @brief Set a system signature (components it needs)
	template<typename T>
	void SetSignature(Signature pSignature);

	/// @brief Get a system signature (components it needs)
	template<typename T>
	Signature GetSignature();
    
	template<typename T>
	std::shared_ptr<System> GetSystem();

    /// @brief Remove/add an entity from/to all the systems when its signature changed
	void EntitySignatureChanged(Entity pEntity, Signature pEntitySignature);
	
	/// @brief Remove an entity from all the systems when it's destroyed
	/// @param pEntity
	void EntityDestroyed(Entity pEntity);

private:
	std::unordered_map<std::string, Signature> _signatures{};
	std::unordered_map<std::string, std::shared_ptr<System>> _systems{};
};

template<typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
    std::string typeName = typeid(T).name();

    assert(_systems.find(typeName) == _systems.end() && "Registering system more than once.");

    auto system = std::make_shared<T>();
    _systems.insert({typeName, system});
    return system;
}

template<typename T>
void SystemManager::SetSignature(Signature pSignature)
{
    std::string typeName = typeid(T).name();

    assert(_systems.find(typeName) != _systems.end() && "System used before registered.");

    _signatures.insert({typeName, pSignature});
}

template<typename T>
Signature SystemManager::GetSignature()
{
    std::string typeName = typeid(T).name();

    assert(_signatures.find(typeName) != _signatures.end() && "System used before set signature.");

    return _signatures[typeName];
}

template<typename T>
std::shared_ptr<System> SystemManager::GetSystem()
{
	std::string typeName = typeid(T).name();

    assert(_systems.find(typeName) != _systems.end() && "System used before registering.");

	return _systems[typeName];
}

#endif // _SYSTEM_MANAGER_HPP_