#if !defined(MOUSE_H)
#define MOUSE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "constants.h"

using namespace std; 
using namespace glm;

/**
 * Structure that stores mouse status 
 * 
 * It tells us: 
 *  - whether the mouse is currently pressed down 
 *  - position in particle's coordinate system 
 */ 
class Mouse
{
    unsigned int x, y; 
    bool down; 
    vec2 bounds; 

    // hide default initializer to force user to call the designated initializer
    Mouse();
    // vec2 windowCoord2WorldCoord(unsigned int _x, unsigned int _y, mat3 camMatrix);
    vec2 windowCoord2NormalizedCoord(unsigned int _x, unsigned int _y) const;

  public: 
    Mouse(vec2 model); 

    // getters
    /**
     * Gets mouse position in particle's cooridinate system. 
     * 
     * Returns vec2(float, float)
     */
    vec2 getMousePosNormalized() const;
    bool isMouseDown();

    // setters
    void handleMouseRelease();
    void handleMouseDown(unsigned int, unsigned int, mat3);
    void handleMouseDrag(unsigned int, unsigned int, mat3);
};

#endif // MOUSE_H
