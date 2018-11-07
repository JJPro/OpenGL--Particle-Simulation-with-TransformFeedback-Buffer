#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "SDLGraphicsProgram.h"
#include "Terrain.h"




// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
    std::cout << "(SDLGraphicsProgram.cpp) Constructor Called\n";
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else{
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // We want to request a double buffer for smooth updating.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create window
    gWindow = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        //Create an OpenGL Graphics Context
        gContext = SDL_GL_CreateContext( gWindow );
        if( gContext == NULL){
            errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Initialize GLAD Library
        if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
            errorStream << "Failed to iniitalize GLAD and OpenGL\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

    // SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
    getOpenGLVersionInfo();


    // Setup our Renderer
    renderer = new Renderer(w,h);
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(renderer!=nullptr){
        delete renderer;
    }

    //Destroy window
    SDL_DestroyWindow( gWindow );
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}


//Loops forever!
void SDLGraphicsProgram::loop(){

    // Create our terrain
    Terrain* myTerrain = new Terrain(512,512,"terrain2.ppm");
    myTerrain->LoadTexture("colormap.ppm");
    // Create a node for our terrain 
    SceneNode* terrainNode;
    terrainNode = new SceneNode(myTerrain);
    // Set our SceneTree up
    renderer->setRoot(terrainNode);


    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text 
    SDL_StartTextInput();

    // Set a default speed for the camera
    float cameraSpeed = 5.0f;

    // While application is running
    while(!quit){
        
        terrainNode->getLocalTransform().loadIdentity();

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboad input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
//                renderer->camera->mouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            renderer->camera->moveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            renderer->camera->moveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            renderer->camera->moveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            renderer->camera->moveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            renderer->camera->moveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            renderer->camera->moveDown(cameraSpeed);
                            break;
                    }
                break;
            }
        } // End SDL_PollEvent loop.

        // Update our scene through our renderer
        renderer->Update();
        // Render our scene using our selected renderer
        renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25); 
        //Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
    }

    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::getOpenGLVersionInfo(){
    SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
    SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
    SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
    SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
