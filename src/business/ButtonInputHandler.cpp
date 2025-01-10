#include "ButtonInputHandler.hpp"
#include <raylib.h>

#include "ecs/core/Coordinator.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Renderable.hpp"

std::string ButtonInputHandler::ToString() const
{
    return "ButtonInputHandler";
}

bool ButtonInputHandler::next(Entity button)
{
    bool    buttonAction = false;
    int     buttonState = 0;
    Vector2 mousePoint   = GetMousePosition();
    
    Transform2 &transform  = Coordinator::GetInstance()->GetComponent<Transform2>(button);
    Renderable &renderable = Coordinator::GetInstance()->GetComponent<Renderable>(button);

    Rectangle rect = Rectangle {
        .x = transform.position.x,
        .y = transform.position.y,
        .width = renderable.rect.width * transform.scale.x,
        .height = renderable.rect.height * transform.scale.y
    };

    if (CheckCollisionPointRec(mousePoint, rect)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            buttonState = 1;
        }
        else {
            buttonState = 0;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            buttonAction = true;
        }
    }
    else {
        buttonState = 0;
    }

    // Calculate button frame rectangle to draw depending on button state
    renderable.rect.x = buttonState * renderable.rect.width;

    return buttonAction;
}
