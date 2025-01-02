#ifndef _ECS_TYPES_HPP_
#define _ECS_TYPES_HPP_

#include <bitset>
#include <cstdint>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 4096;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // _ECS_TYPES_HPP_