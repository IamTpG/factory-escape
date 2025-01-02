#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <string>

/// @brief Abstract class to create all the other classes
class Object {
public:
    virtual ~Object() = default;
    virtual std::string ToString() const = 0;
};

#endif // _OBJECT_HPP_

