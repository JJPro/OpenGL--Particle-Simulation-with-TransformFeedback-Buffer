#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "Buffer.h"
#include "Object.h"

// Purpose:
// This class sets up a full graphics program using SDL
//
//
//
class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Desctructor
    ~SDLGraphicsProgram();
    // Setup OpenGL
    bool initGL();
    // Per frame update
    void update();
    // Renders shapes to the screen
    void render();
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Helper Function to Query OpenGL information.
    void getOpenGLVersionInfo();

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // OpenGL context
    SDL_GLContext gContext;
    // My object
    Object* myObject;
};

#endif
