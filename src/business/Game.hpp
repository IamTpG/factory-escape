#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <raylib.h>
#include <memory>
#include <vector>

#include "../models/Object.hpp"
#include "../models/Level.hpp"

#include "../business/ecs/core/ECSTypes.hpp"
#include "ecs/core/System.hpp"

/// @brief Main class
class Game : public Object {
public:
    virtual std::string ToString() const override;

public:
    /// @brief Load all the resources
    void Init();

    /// @brief Main game loop here
    void Run();

    /// @brief Clean up all the loaded resources
    void Shutdown();

public:
    /// @brief Recieve and handle user input (keyboard, mouse)
    void HandleInput();

    /// @brief Apply game logic to update objects
    void Update();

    /// @brief Render all the objects and display them on the screen
    void Render();

private:
    bool _dragging;
    Texture2D _grid;
    std::shared_ptr<System> _colliderSystem, _physicsSystem, _rendererSystem;

    Level* level;
};

#endif // _GAME_HPP_