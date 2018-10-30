#include "SDLGraphicsProgram.h"




// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
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
                                screenWidth,
                                screenHeight,
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
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!initGL()){
			errorStream << "Unable to initialize OpenGL!\n";
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


    // Setup our objects
    myObject = new Object();
    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    // Reclaim all of our objects
    delete myObject;

    //Destroy window
	SDL_DestroyWindow( gWindow );
	// Point gWindow to NULL to ensure it points to nothing.
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL(){
	//Success flag
	bool success = true;

    // Setup our OpenGL State machine
    // TODO: Read this
    // The below command is new!
    // What we are doing, is telling opengl to create a depth(or Z-buffer) 
    // for us that is stored every frame.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
	return success;
}


// Update OpenGL
void SDLGraphicsProgram::update(){

    static float rot = 0;
    rot+=0.01;
    if(rot>360){rot=0;}


    myObject->getTransform().loadIdentity();
    myObject->getTransform().translate(0.0f,0.0f,-8.0f);
    myObject->getTransform().rotate(rot,0.0f,1.0f,0.0f);
    myObject->getTransform().scale(2.0f,2.0f,2.0f);
    myObject->update(screenWidth,screenHeight);
}



// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render(){
    // Initialize clear color
    // This is the background of the screen.
    glViewport(0, 0, screenWidth, screenHeight);
    glClearColor( 0.2f, 0.2f, 0.2f, 1.f );
    // TODO: Read this
    // Clear color buffer and Depth Buffer
    // Remember that the 'depth buffer' is our
    // z-buffer that figures out how far away items are every frame
    // and we have to do this every frame!
  	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    (*myObject).render(); // Equivalent to myObject->render();
   
    SDL_Delay(50); 
}


//Loops forever!
void SDLGraphicsProgram::loop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while(!quit){
     	 //Handle events on queue
		while(SDL_PollEvent( &e ) != 0){
        	// User posts an event to quit
	        // An example is hitting the "x" in the corner of the window.
    	    if(e.type == SDL_QUIT){
        		quit = true;
	        }
      	} // End SDL_PollEvent loop.

		// Update our scene
		update();
		// Render using OpenGL
	    render(); 	// TODO: potentially move this depending on your logic
					// for how you handle drawing a triangle or rectangle.
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
