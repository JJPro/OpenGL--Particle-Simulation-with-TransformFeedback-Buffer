#include "SDLGLProgram.h"
#define REFRESH_DELAY 20

SDLGLProgram::SDLGLProgram(int w, int h) : screenWidth(w), screenHeight(h)
{
    std::stringstream errorStream;
    window = NULL;

    if (!initSDL() || !initGL())
    {
        errorStream << typeid(this).name() << "Failed to initialize!" << std::endl;
        SDL_Log("%s\n", errorStream.str().c_str());
    }
    else
    {
        SDL_Log("Initialization success!\n");
        getOpenGLVersionInfo();

        // glEnable(GL_DEPTH_TEST);
    }
}

// update state for every render
void SDLGLProgram::update()
{
}

// sets what to render
void SDLGLProgram::render()
{
    /***** cleaning work *****/
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor(.5, .5, .5, 1);  
    glClear(GL_COLOR_BUFFER_BIT); 

    /****** draw objects ******/
    // TODO 
}

void SDLGLProgram::loop()
{

    SDL_Event e;
    while (e.type != SDL_QUIT)
    {
        // event handler changes our state, then we can use the state for updates and rendering
        eventHandler(e);

        update();
        render();

        SDL_GL_SwapWindow(window);
        fixMojaveBlackScreen();
        // Delay to slow things down just a bit!
        SDL_Delay(REFRESH_DELAY);
    }
}

SDLGLProgram::~SDLGLProgram()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

/** TODO 
# Interactivity 
### Mouse 
| Control      | Description                                       |
| ------------ | ------------------------------------------------- |
| Scroll Wheel | Zoom In/Out                                       | 
| Click        | Applys gratational force to surrounding particles | 

### Keyboard 
| Control    | Description |
| ---------- | ----------- |
| Left⇧      | Zoom In     | 
| Left⌃      | Zoom Out    | 
| ←, ↑, →, ↓ | Move Around | 
*/
void SDLGLProgram::eventHandler(SDL_Event e)
{
    while (SDL_PollEvent(&e))
    {
        // handle user interaction here
        switch (e.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            exit(0);
            break;
        case SDL_MOUSEMOTION:
            // handle mouse motion here
            break;
        case SDL_KEYDOWN:
            // handle keyboard events here
            switch (e.key.keysym.sym)
            {
            case SDLK_q:
                SDL_Quit();
                exit(0);
                break;
            }
            break;

        default:
            break;
        }
    }
}

bool SDLGLProgram::initGL()
{
    SDL_Log("setting up OpenGL...");
    bool success = true;
    std::stringstream errorStream;

    // set OpenGL context version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // set OpenGL profile version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // request for double buffer for smooth updating
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // create OpenGL context
    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    // initialize opengl glad helper lib
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        errorStream << "Failed to initialize GLAD" << std::endl;
        success = false;
    }

    if (!success)
    {
        SDL_Log("%s\n", errorStream.str().c_str());
        return false;
    }
    else
    {
        return true;
    }
}
bool SDLGLProgram::initSDL()
{
    SDL_Log("Setting up SDL...");
    bool success = true;
    std::stringstream errorStream;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    window = SDL_CreateWindow("Lab",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth, screenHeight,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window)
    {
        errorStream << "Failed to create window!" << std::endl;
        success = false;
    }
    if (!success)
    {
        SDL_Log("%s\n", errorStream.str().c_str());
        return false;
    }
    else
    {
        return true;
    }
}

// Helper Function to get OpenGL Version Information
void SDLGLProgram::getOpenGLVersionInfo()
{
    SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
    SDL_Log("Vendor: %s", (const char *)glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s", (const char *)glGetString(GL_RENDERER));
    SDL_Log("Version: %s", (const char *)glGetString(GL_VERSION));
    SDL_Log("Shading language: %s", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void SDLGLProgram::fixMojaveBlackScreen()
{
    static bool fixed = false;
    if (fixed)
        return;
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    SDL_SetWindowPosition(window, x, y);
    fixed = true;
}
