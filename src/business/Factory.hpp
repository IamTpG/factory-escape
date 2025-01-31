#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include <raylib.h>
#include <map>
#include <vector>
#include <typeinfo>
#include <memory>

#include "../models/Object.hpp"

#include "ecs/core/ECSTypes.hpp"
#include "ecs/core/System.hpp"

/// @brief Class to create needed systems and entities
///
/// In ECS, each system and entity has its signature.
/// This factory class helps create some frequently used systems and entities.
class Factory : public Object {
private:
    inline static std::shared_ptr<Factory> _instance;

    // Hide constructor for singleton pattern
    Factory();

public:
    virtual std::string ToString() const override;

public:
    static std::shared_ptr<Factory> GetInstance();

    std::shared_ptr<System> CreateColliderSystem();
    std::shared_ptr<System> CreatePhysicsSystem();
    std::shared_ptr<System> CreateRendererSystem();

    Entity CreateCharacter(Vector2 pPosition);
    Entity CreateDecorativeTile(Vector2 pPosition, int pId);
    Entity CreateSolidTile(Vector2 pPosition, int pId);
    Entity CreateDraggableTile(Vector2 pPosition, int pId);
    Entity CreatePortalTile(Vector2 pPosition);

    Entity CreateButton(Vector2 pPosition, int pId);
};

#endif // _FACTORY_HPP_