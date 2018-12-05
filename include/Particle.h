#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include "constants.h"
#include "Mouse.h"
#include "constants.h"

using namespace glm;
using namespace std; 

struct Particle
{
    vec2 acceleration; 
    vec2 speed; 
    vec2 pos; 

    Particle(vec2 _pos)
    {
        pos = _pos; 
        acceleration = vec2(0); 
        speed = vec2(0); 
    }

    string toString(); 
};

#endif
