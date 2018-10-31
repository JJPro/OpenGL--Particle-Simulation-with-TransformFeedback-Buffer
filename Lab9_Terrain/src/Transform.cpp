#include "Transform.h"
#include <iostream>

Transform::Transform(){
	std::cout << "(Transform.cpp) Constructor Called\n";
    modelTransformMatrix = glm::mat4();
}

Transform::~Transform(){

}

// Resets the model transform as the identity matrix.
void Transform::loadIdentity(){
    modelTransformMatrix = glm::mat4();
}

void Transform::translate(float x, float y, float z){
        // Here we apply our camera
        // This first transformation is applied to the object
        // This is the model transform matrix.
        // That is, 'how do I move our model'
        // Here we see I have translated the model -1.0f away from its original location.
        // We supply the first argument which is the matrix we want to apply
        // this transformation to (Our previous transformation matrix. 
        modelTransformMatrix = glm::translate(modelTransformMatrix,glm::vec3(x,y,z));                            
}

void Transform::rotate(float radians, float x, float y, float z){
    modelTransformMatrix = glm::rotate(modelTransformMatrix, radians, glm::vec3(x,y,z));        
}

void Transform::scale(float x, float y, float z){
    modelTransformMatrix = glm::scale(modelTransformMatrix,glm::vec3(x,y,z));        
}

// Returns the actual transform matrix
// Useful for sending 
GLfloat* Transform::getTransformMatrix(){
    return &modelTransformMatrix[0][0];
}


// Get the raw internal matrix from the class
glm::mat4 Transform::getInternalMatrix() const{
    return modelTransformMatrix;
}

void Transform::applyTransform(Transform t){
    modelTransformMatrix = t.getInternalMatrix();
}

// Perform a matrix multiplication with our Transform
Transform& Transform::operator*(const Transform& t) {
	modelTransformMatrix =  modelTransformMatrix * t.getInternalMatrix();
	return *this;
}
