#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <raylib.h>

/// @brief Entity's component
struct Transform2 {
	Vector2 position;
	Vector2 scale;
	float   rotation;
};

#endif // _TRANSFORM_HPP_