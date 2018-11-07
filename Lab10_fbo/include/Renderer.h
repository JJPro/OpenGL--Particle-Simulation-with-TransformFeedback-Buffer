#ifndef RENDERER_H
#define RENDERER_H
/** @file Renderer.h
 *  @brief Renderer is responsible for drawing.
 *
 * 	Renderer is responsible for drawing everything. It
 *	contains a scenegraph node and a camera. We could 
 *	possibly have multiple renderers (if we had multiple
 *	windows for example).
 *
 *	Each renderer thus has it's own camera.
 *
 *  @author Mike
 *  @bug No known bugs.
 */

// The glad library helps setup OpenGL extensions.
// This renderer is designed specifically for OpenGL.
#include <glad/glad.h>

#include <vector>

#include "SceneNode.h"
#include "Camera.h"
#include "FrameBuffer.h"

class Renderer{
public:
    // The constructor	
    // Sets the width and height of the rendererer draws to
    Renderer(unsigned int w, unsigned int h);
    // Destructor
    ~Renderer();
    // Update the scene
    void Update();
    // Render the scene
    void Render();
    // Sets the root of our renderer to some node to
    // draw an entire scene graph
    void setRoot(SceneNode* n);
// TODO: Do not necessarily need to make this public
    // The one camera per Renderer
    Camera* camera;
    // TODO:(Optional)  write getter/setter methods
    
    // A renderer can have any number of framebuffers
    // For now, let's just initialize one.
    Framebuffer* myFramebuffer;
protected:
    // Root scene node
    SceneNode* root;
    // Store the projection matrix for our camera.
    glm::mat4 projectionMatrix;

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
};

#endif
