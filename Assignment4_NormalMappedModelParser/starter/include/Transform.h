#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// The purpose of this class is to store
// transformations of 3D entities (cameras, objects, etc.)
class Transform{
public:

    Transform();

    ~Transform();

    // Resets matrix transformations to the identity matrix
    void loadIdentity();
    // Perform a translation of an object
    void translate(float x, float y, float z);
    // Perform rotation about an axis
    void rotate(float radians, float x, float y, float z);
    // Perform rotation about an axis
    void scale(float x, float y, float z);
    // Returns the transformation matrix
    GLfloat* getTransformMatrix();
    // Apply Transform
    // Takes in a transform and sets internal
    // matrix.
    void applyTransform(Transform t);
    // Returns the transformation matrix
    glm::mat4 getInternalMatrix();
private:
    glm::mat4 modelTransformMatrix;
};


#endif
