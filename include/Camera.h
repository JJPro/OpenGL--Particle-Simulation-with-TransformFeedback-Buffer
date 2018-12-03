#if !defined(CAMERA_H)
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>


using namespace glm;
class Camera 
{
private: 
    vec2 pos; 
    float zoom; 
public: 
    Camera() : pos(vec2(0)), zoom(1) {}
    ~Camera(); 

    mat3 getWorldToViewMatrix() const; 

    void zoomIn(float speed);
    void zoomOut(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
    void moveUp(float speed);
    void moveDown(float speed);

};


#endif // CAMERA_H
