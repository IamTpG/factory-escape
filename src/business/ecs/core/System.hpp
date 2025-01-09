#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include <set>

#include "../../../models/Object.hpp"
#include "ECSTypes.hpp"

/// @brief System base (abstract) class
class System : public Object {
public:
	virtual std::string ToString() const override;

public:
	virtual void Update(float deltaTime = 0.0f);

public:
	std::set<Entity> entities;
};

#endif // _SYSTEM_HPP_
