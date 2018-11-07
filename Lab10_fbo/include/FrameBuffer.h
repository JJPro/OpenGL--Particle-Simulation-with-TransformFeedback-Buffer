/** @file Framebuffer.h
 *  @brief Creates an offscreen texture to render to.
 *
 * The 'Create' function needs to be called before using the  
 * framebuffer.
 *
 *  @author Mike
 *  @bug No known bugs.
 *
 */
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include "Shader.h" // Each Framebuffer can have a custom shader

class Framebuffer{
public:
    // Default Constructor
    Framebuffer();
    // Destructor
    ~Framebuffer();
    // Create the framebuffer
    void Create(int width, int height);
    // Select our framebuffer
    void Bind();
    // Update our framebuffer once per frame for any
    // changes that may have occurred.
    void Update();
    // Done with our framebuffer
    void Unbind();
    // Draws the screen quad
    void drawFBO();
private: 
    // Creates a quad that will be overlaid on top of the screen
    // TODO: add x1,x2, etc. to draw FBO over a range in the scene.
    void setupScreenQuad(float x1,float x2, float y1, float y2);
// public member variables
public:
    Shader* fboShader;
    // Our framebuffer also needs a texture.
    unsigned int colorBuffer_id;
// private member variables
private:
    // Framebuffer id
    unsigned int fbo_id; 
    // Finally create our render buffer object
    unsigned int rbo_id;
    // Store our screen buffer
    unsigned int quadVAO, quadVBO;

};

#endif
