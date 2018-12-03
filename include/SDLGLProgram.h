
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "Shader.h"
// #include "Object.h"

class SDLGLProgram
{

public:
  SDLGLProgram(int w, int h);
  ~SDLGLProgram();

  void loop();

private:
  int screenHeight, screenWidth;
  SDL_Window *window;
  SDL_GLContext context;

  void update();
  void render();

  void eventHandler(SDL_Event e);
  /**
   * create GL context 
   */
  bool initGL();
  /**
   * create window
   */
  bool initSDL();
  void getOpenGLVersionInfo();
  void fixMojaveBlackScreen();
};
