#ifndef _ENTITY_MANAGER_HPP_
#define _ENTITY_MANAGER_HPP_

#include <array>
#include <cassert>
#include <queue>

#include "../../../models/Object.hpp"
#include "ECSTypes.hpp"

/// @brief Class to manage entities
class EntityManager : public Object
{
public:
    std::string ToString() const override;

public:
	/// @brief Initialize
	EntityManager();

	/// @brief Register a new id from a new entity
	Entity CreateEntity();

	/// @brief Destroy an entity and set it's id free to use
	void DestroyEntity(Entity pEntity);

	/// @brief Set an entity signature (its components)
	void SetSignature(Entity pEntity, Signature pSignature);

	/// @brief Get an entity signature (its components)
	Signature GetSignature(Entity pEntity);

private:
	std::queue<Entity> _availableEntities{};
	std::array<Signature, MAX_ENTITIES> _signatures{};
	uint32_t _livingEntityCount{};
};

#endif // _ENTITY_MANAGER_HPP_