#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include "FrameBuffer.h"
#include <glad/glad.h>


Framebuffer::Framebuffer(){
    // (1) ======= Setup shader
    fboShader = new Shader;
    // Setup shaders for the Framebuffer Object
    std::string fboVertexShader = fboShader->LoadShader("./shaders/fboVert.glsl");
    std::string fboFragmentShader = fboShader->LoadShader("./shaders/fboFrag.glsl");
    // Actually create our shader
    fboShader->CreateShader(fboVertexShader,fboFragmentShader);       
    // (2) ======= Setup quad to draw to
    // Setup the screen quad
    setupScreenQuad(0,0,0,0);
}

// Destructor
Framebuffer::~Framebuffer(){
    glDeleteFramebuffers(1,&fbo_id); 
    delete fboShader;
    glDeleteVertexArrays(1,&quadVAO);
    glDeleteBuffers(1,&quadVBO);
}


// Create the framebuffer
// We create this in a second step, because we need
// width and height information
// TODO: What happens if the window resizes?
//       Answer: Need to regenerate our buffer
void Framebuffer::Create(int width, int height){

    // Generate a framebuffer
    glGenFramebuffers(1, &fbo_id);
    // Select the buffer we have just generated
    Bind();
    // Create a color attachement texture
    glGenTextures(1, &colorBuffer_id);
    glBindTexture(GL_TEXTURE_2D, colorBuffer_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorBuffer_id,0);
    // Create our render buffer object
    glGenRenderbuffers(1,&rbo_id);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,width,height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);
    // Deselect our buffers
    Unbind();
}
// Select our framebuffer
void Framebuffer::Bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
}

// Update our framebuffer once per frame for any
// changes that may have occurred.
void Framebuffer::Update(){
    // Select our framebuffer
    fboShader->Bind();
    // Set the uniforms in our current shader

    // For our object, we apply the texture in the following way
    // Note that we set the value to 0, because we have bound
    // our texture to slot 0.
    fboShader->setUniform1i("u_DiffuseMap",0);  
}

// Done with our framebuffer
void Framebuffer::Unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

// Draws the screen quad
// This is the actual rendering of our FBO to the screen.
// Typically this would be called after 'update'
void Framebuffer::drawFBO(){
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, colorBuffer_id);   // use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

// ============== Private Member Functions ==============
// ============== Private Member Functions ==============
// ============== Private Member Functions ==============

// Creates a quad that will be overlaid on top of the screen
// TODO: add x1,x2, etc. to draw FBO over a range in the scene.
void Framebuffer::setupScreenQuad(float x1,float x2, float y1, float y2){

    float quad[] = {
        // First triangle
        -1.0f,  1.0f,  0.0f, 1.0f, // x,y,s,t
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        // Second triangle
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

// screen quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));

}
