#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

// Game config goes here

#define TILE_WIDTH_COUNT    15
#define TILE_HEIGHT_COUNT   10
#define TILE_SIZE           64

#define SCREEN_OFFSET       20

#define SCREEN_WIDTH        (2 * SCREEN_OFFSET + TILE_WIDTH_COUNT * TILE_SIZE)
#define SCREEN_HEIGHT       (2 * SCREEN_OFFSET + TILE_HEIGHT_COUNT * TILE_SIZE)

#define TITLE               "Factory Escape"
#define GAME_FPS            60

#define CHARACTER_PATH      "assets/character.png"
#define FACTORY_PATH        "assets/factory.png"

#define GRAVITY             16.0f
#define CHARACTER_SPEED_X   6.0f
#define CHARACTER_SPEED_Y   8.0f

#endif // _CONFIG_HPP_
