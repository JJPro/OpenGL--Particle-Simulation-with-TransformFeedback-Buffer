#include "Camera.h"

Camera::~Camera()
{}

mat3 Camera::getViewMatrix() const
{
    mat3 trans; 
    trans = translate(trans, pos); 
    trans = scale(trans, vec2(zoom)); 
    return trans;
}

void Camera::zoomIn(float speed)
{
    zoom *= speed; 
}
void Camera::zoomOut(float speed)
{
    zoom /= speed;
}
void Camera::moveLeft(float speed)
{
    pos.x -= speed*0.03f; 
}
void Camera::moveRight(float speed)
{
    pos.x += speed*0.03f;
}
void Camera::moveUp(float speed)
{
    pos.y += speed*0.03f;
}
void Camera::moveDown(float speed)
{
    pos.y -= speed*0.03f;
}