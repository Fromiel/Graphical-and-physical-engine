#ifndef ECS_H
#define ECS_H

#include <bitset>

using Entity = size_t;

const Entity MAX_ENTITIES = 5000;

// A simple type alias
using ComponentType = size_t;

// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;


#endif