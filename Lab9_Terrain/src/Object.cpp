#include "Object.h"
#include "Camera.h"

#include <iostream>


Object::Object(){
    std::cout << "(Object.cpp) Constructor called\n";    
//    init(); // TODO: Today we do not need a default quad.
}

Object::~Object(){
    
}

// TODO: In the future it may be good to 
// think about loading a 'default' texture
// if the user forgets to do this action!
void Object::LoadTexture(std::string fileName){
        // Load our actual textures
        diffuseMap.LoadTexture(fileName);
}


// Initialization of object
// This could be called in the constructor, or
// it is more typicaly to 'explicitly' call this
// so we create our objects at the correct time
void Object::init(){
        // Setup geometry
        // Be careful not to forget comma's after each line
        // (except the last line of course)!	
        geometry.addVertex(-1.0f,-1.0f,0.0f);   // Position
        geometry.addTexture(0.0f,0.0f);         // Texture

        geometry.addVertex(1.0f,-1.0f,0.0f);   // Position
        geometry.addTexture(1.0f, 0.0f);        // Texture

        geometry.addVertex(1.0f,1.0f,0.0f);    // Position
        geometry.addTexture(1.0f, 1.0f);        // Texture

        geometry.addVertex(-1.0f,1.0f,0.0f);   // Position
        geometry.addTexture(0.0f, 1.0f);        // Texture
        // Make our triangles and populate our
        // indices data structure	
        geometry.makeTriangle(0,1,2);
        geometry.makeTriangle(2,3,0);

        geometry.gen();

        // Create a buffer and set the stride of information
        myBuffer.CreateBufferNormalMapLayout(14,
                                            geometry.getSize(),
                                            geometry.getIndicesSize(),
                                            geometry.getData(),
                                            geometry.getIndicesData());
}


// Bind everything we need in our object
// Generally this is called in update() and render()
// before we do any actual work with our object
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        myBuffer.Bind();
        // Diffuse map is 0 by default, but it is good to set it explicitly
        diffuseMap.Bind(0);
}

void Object::render(){
     Bind();
    //Render data
    glDrawElements(GL_TRIANGLES,
                    geometry.getIndicesSize(),               // The number of indicies, not triangles.
                    GL_UNSIGNED_INT, // Make sure the data type matches
                    nullptr);       // Offset pointer to the data. nullptr because we are currently bound:	
}

