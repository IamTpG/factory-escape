/*
    This file contains main function.
    The program starts and ends here.

    F5 to compile and run the program.
    "Raylib" folder should be directly in drive C:
*/

#include "FactoryEscape.hpp"

int main()
{
    Game* game = new Game();
    
    game->Init();
    game->Run();
    game->Shutdown();
    
    delete game;
    return 0;
}

/*
    // Compile paths

    src\\*.cpp
    src\\business\\*.cpp
    src\\business\\ecs\\core\\*.cpp
    src\\business\\ecs\\systems\\*.cpp
*/
