#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>

class Game {
private:

public:
    Game();
    ~Game();
public:
    void loop();
    void input();
    void update();
    void draw();
};

#endif // GAME_HPP
