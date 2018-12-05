#include "SDLGLProgram.h"

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
        mouse = new Mouse(vec2(BOX_EDGE_LEN)); 

        // set up shader file 
        shader = new Shader("shaders/vert.glsl", "shaders/frag.glsl");

        shader->use();
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_PROGRAM_POINT_SIZE);
        shader->setUniform("PARTICLE_SPEED_MAX", PARTICLE_SPEED_MAX);
        shader->setUniform("GRAVITATIONAL_CONSTANT", GRAVITATIONAL_CONSTANT);
        shader->setUniform("PARTICLE_ACCELERATION_MAX", PARTICLE_ACCELERATION_MAX);
        shader->setUniform("PARTICLE_MOVING_RESISTENCE", PARTICLE_MOVING_RESISTENCE);
        float tmp = ((float)BOX_EDGE_LEN) / 2;
        vec4 boxBounds = vec4(vec2(-tmp, tmp),  // up-left corner
                              vec2(tmp, -tmp)); // bottom-right corner
        shader->setUniform("boxBounds", boxBounds);

        // buffer initial data to GPU
        initBufferData();
    }
}

/**
 * Sets up the initial states of the particles and buffer them to GPU 
 */
void SDLGLProgram::initBufferData()
{
    int particles_per_row = sqrt(PARTICLE_COUNT);
    float gap = BOX_EDGE_LEN / particles_per_row; // gap distance between particles

    vec2 pos; 
    for(int i=0; i < particles_per_row; i++){ // row
        for(int j=0; j<particles_per_row; j++){ // column
            pos.x = j * gap - BOX_EDGE_LEN/2; pos.y = i * gap - BOX_EDGE_LEN/2; 
            particles.push_back(Particle(pos)); 
        }
    }

    _genBuffers(); 
    _bufferParticles(); 
}



// update state for every render
void SDLGLProgram::update()
{
    shader->use(); 
    shader->setUniform("camMatrix", camera.getViewMatrix()); 
    shader->setUniform("Mouse.isMouseDown", mouse->isMouseDown());
    shader->setUniform("Mouse.mousePos", mouse->getMousePosInLocalCoord(camera.getViewMatrix()));
}

// sets what to render
void SDLGLProgram::render()
{
    /***** cleaning work *****/
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor(.5, .5, .5, 1);  
    glClear(GL_COLOR_BUFFER_BIT); 

    /****** draw objects ******/
    shader->use(); 
    static bool first_render = true; 

    if (first_render) {
        renderBufferIndex = 0; 
        feedbackBufferIndex = 1;
        first_render = false; 
    } else {
        renderBufferIndex = feedbackBufferIndex; 
        feedbackBufferIndex = 1 - renderBufferIndex; 
    }


    // first draw, capture the vertices 
    glEnable(GL_RASTERIZER_DISCARD);
    
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO[feedbackBufferIndex]);
        glBindVertexArray(VAO[renderBufferIndex]); 

        glBeginTransformFeedback(GL_POINTS); 
            glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT); 
        glEndTransformFeedback(); 

    glDisable(GL_RASTERIZER_DISCARD);


    // second draw, reuse the captured vertices
    glBindVertexArray(VAO[renderBufferIndex]); 
    glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT); 
    

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
    _delBuffers();
    delete mouse; 
    mouse = NULL; 

    delete shader; 
    shader = NULL; 
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
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
                mouse->handleMouseDown(e.button.x, e.button.y, camera.getViewMatrix()); 
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT)
                mouse->handleMouseRelease(); 
            break;
        case SDL_MOUSEWHEEL:
            if (e.wheel.y > 0)
                camera.zoomOut(CAM_SPEED);
            else
                camera.zoomIn(CAM_SPEED);
            break;
        case SDL_MOUSEMOTION: // handle mouse drag
            if (mouse->isMouseDown())
                mouse->handleMouseDrag(e.button.x, e.button.y, camera.getViewMatrix());
            break; 
        case SDL_KEYDOWN:
            // handle keyboard events here
            switch (e.key.keysym.sym)
            {
                case SDLK_q:
                    SDL_Quit();
                    exit(0);
                    break;
                case SDLK_LEFT:
                    camera.moveLeft(CAM_SPEED);
                    break;
                case SDLK_RIGHT:
                    camera.moveRight(CAM_SPEED);
                    break;
                case SDLK_UP:
                    camera.moveUp(CAM_SPEED);
                    break;
                case SDLK_DOWN:
                    camera.moveDown(CAM_SPEED);
                    break;
                case SDLK_LSHIFT:
                    camera.zoomIn(CAM_SPEED);
                    break;
                case SDLK_LCTRL:
                    camera.zoomOut(CAM_SPEED);
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

void SDLGLProgram::_bufferParticles()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); 
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), NULL, GL_DYNAMIC_DRAW);

    /**
     * Configure Buffer Layout
     * 
     * Note: 
     * Make sure that layout is only set once, 
     * because buffer layout stays the same for all subsequent usage. 
     * This way, we could save significant amount of GL calls. 
     */
    static bool layout_set = false;
    if (layout_set)
        return;
    
    for (int i=0; i<2; i++){

        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        // vec2 acceleration
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
        glEnableVertexAttribArray(0);
        // vec2 speed
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // vec2 pos
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void *)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    layout_set = true;
}

void SDLGLProgram::_genBuffers()
{
    /**
     * Generate VAO and VBO buffers
     * 
     * Also make sure the buffers are only created once. 
     */
    static bool generated = false;
    if (generated)
        return;
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    generated = true;
}
void SDLGLProgram::_delBuffers()
{
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
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

void SDLGLProgram::printParticles()
{
    cout << ">>>>>>>>> " << endl;
    cout << "   test particles: " << endl;
    cout << "     " << particles[1].toString() << endl; 
    // for (int i=0; i<5; i++){
    //     cout << "     " << particles[i].toString() << endl; 
    // }
    cout << "<<<<<<<< " << endl;
}