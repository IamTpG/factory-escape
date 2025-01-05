#include "DraggableTileInputHandler.hpp"
#include "../models/Config.hpp"

#include <raylib.h>

#include "ecs/core/Coordinator.hpp"
#include "ecs/components/Draggable.hpp"
#include "ecs/components/Collider.hpp"
#include "ecs/components/Transform.hpp"

std::string DraggableTileInputHandler::ToString() const
{
    return "DraggableTileInputHandler";
}

bool DraggableTileInputHandler::next(Entity tile)
{
    Signature signature = Coordinator::GetInstance()->GetEntitySignature(tile);
    ComponentType draggableType = Coordinator::GetInstance()->GetComponentType<Draggable>();
    
    /*
        If the tile does not have draggable component then skip
    */
    if (signature.test(draggableType) == false) {
        return false;
    }

    Draggable   &draggable  = Coordinator::GetInstance()->GetComponent<Draggable>(tile);
    Collider    &collider   = Coordinator::GetInstance()->GetComponent<Collider>(tile);
    Transform2  &transform  = Coordinator::GetInstance()->GetComponent<Transform2>(tile);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();

        /*
            Sometimes the cursor goes outside the collider but it still "holds" the tile.
            To handle this, we add a variable to check if the tile's still being dragged.
        */
        if (CheckCollisionPointRec(mousePosition, collider.boundary)) {
            draggable.dragging = true;
        }

        if (draggable.dragging == true) {
            transform.position.x = mousePosition.x;
            transform.position.y = mousePosition.y;

            collider.boundary.x = mousePosition.x;
            collider.boundary.y = mousePosition.y;

            /*
                The tile should be automatically alligned
            */
            transform.position.x = int((transform.position.x - SCREEN_OFFSET) / TILE_SIZE) * TILE_SIZE + SCREEN_OFFSET;
            transform.position.y = int((transform.position.y - SCREEN_OFFSET) / TILE_SIZE) * TILE_SIZE + SCREEN_OFFSET;
            collider.boundary.x  = int((collider.boundary.x  - SCREEN_OFFSET) / TILE_SIZE) * TILE_SIZE + SCREEN_OFFSET;
            collider.boundary.y  = int((collider.boundary.y  - SCREEN_OFFSET) / TILE_SIZE) * TILE_SIZE + SCREEN_OFFSET;
        }
    }

    /*
        Release the tile
    */
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        draggable.dragging = false;
    }
    
    return draggable.dragging;
}
