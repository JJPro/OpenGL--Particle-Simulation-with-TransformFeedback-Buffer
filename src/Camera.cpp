#include "Camera.h"

Camera::~Camera()
{}

mat3 Camera::getWorldToViewMatrix() const
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
    pos.x -= speed; 
}
void Camera::moveRight(float speed)
{
    pos.x += speed;
}
void Camera::moveUp(float speed)
{
    pos.y += speed;
}
void Camera::moveDown(float speed)
{
    pos.y -= speed;
}