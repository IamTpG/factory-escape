#ifndef _FLOAT_HPP_
#define _FLOAT_HPP_

#include <raymath.h>

inline bool FloatLessThan(float x, float y)
{
    bool result = (FloatEquals(x, y) == false && x < y);
    return result;
}

inline bool FloatLessThanOrEquals(float x, float y)
{
    bool result = (FloatLessThan(x, y) || FloatEquals(x, y));
    return result;
}


inline bool FloatGreaterThan(float x, float y)
{
    bool result = (FloatEquals(x, y) == false && x > y);
    return result;
}

inline bool FloatGreaterThanOrEquals(float x, float y)
{
    bool result = (FloatGreaterThan(x, y) || FloatEquals(x, y));
    return result;
}

#endif // _FLOAT_HPP_
