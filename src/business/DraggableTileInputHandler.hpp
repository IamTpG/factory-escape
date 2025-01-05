#ifndef _DRAGGABLE_TILE_INPUT_HANDLER_HPP_
#define _DRAGGABLE_TILE_INPUT_HANDLER_HPP_

#include "../models/Object.hpp"
#include "ecs/core/ECSTypes.hpp"

/// @brief Class to handle dragging tiles
class DraggableTileInputHandler : public Object {
public:
    virtual std::string ToString() const override;
public:
    bool next(Entity tile);
};

#endif // _DRAGGABLE_TILE_INPUT_HANDLER_HPP_