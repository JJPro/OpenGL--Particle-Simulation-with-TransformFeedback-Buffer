#include "Mouse.h"

Mouse::Mouse(vec2 _bounds) : bounds(_bounds) {}

vec2 Mouse::getMousePosNormalized() const
/**
 * TODO: convert mouse pos from window space to particle's coordinate system
 * 1. convert to model space
 * 2. convert to view matrix with camMatrix
 */
{
    return windowCoord2NormalizedCoord(x, y); 
}
bool Mouse::isMouseDown()
{
    return down; 
}

void Mouse::handleMouseRelease()
{
    down = false; 
}
void Mouse::handleMouseDown(unsigned int _x, unsigned int _y, mat3 camMatrix)
{
    // test if click is effective (effective if click falls within box's boundaries)
    //    set down = false if click is out of boundary and return early
    vec2 clickPosNormalized = windowCoord2NormalizedCoord(_x, _y);
    float tmp = ((float)BOX_EDGE_LEN)/2; 
    vec4 boxBounds = vec4( vec2(camMatrix * vec3( vec2(-tmp, tmp), 0)),  // up-left corner
                           vec2(camMatrix * vec3( vec2(tmp, -tmp), 0))); // bottom-right corner
    bool clickedInBox = (clickPosNormalized.x >= boxBounds.x)
                     && (clickPosNormalized.y <= boxBounds.y)
                     && (clickPosNormalized.x <= boxBounds.z)
                     && (clickPosNormalized.y >= boxBounds.w);


    // cout << "tmp: " << tmp << endl; 
    // cout << "mouse pos normalized: " << to_string(clickPosNormalized) << endl; 
    // cout << "bounds: " << to_string(boxBounds) << endl; 

    if (clickedInBox)
    {
        down = true; 
        x = _x; y = _y; 
        // cout << "clicked in box" << endl; 
    } else {
        down = false; 
    }
}
void Mouse::handleMouseDrag(unsigned int _x, unsigned int _y, mat3 camMatrix)
{
    handleMouseDown(_x, _y, camMatrix); 
}


/*************************/
/******** Private ********/
/*************************/

vec2 Mouse::windowCoord2NormalizedCoord(unsigned int _x, unsigned int _y) const
{
    int data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    int width = data[2], height = data[3];
    vec2 normalizedPos;
    normalizedPos.x = ((float)_x - (float)width / 2) / ((float)width / 2);
    normalizedPos.y = ((float)height / 2 - (float)_y) / ((float)height / 2);

    return normalizedPos;
}
// vec2 Mouse::windowCoord2WorldCoord(unsigned int _x, unsigned int _y, mat3 camMatrix)
// {
//     int data[4];
//     glGetIntegerv(GL_VIEWPORT, data);
//     int width = data[2], height = data[3];
//     vec2 normalizedPos;
//     normalizedPos.x = ((float)_x - (float)width / 2) / ((float)width / 2);
//     normalizedPos.y = ((float)height / 2 - (float)_y) / ((float)height / 2);
//     vec2 worldPos = vec2(camMatrix * vec3(normalizedPos, 0));

//     return worldPos; 
// }