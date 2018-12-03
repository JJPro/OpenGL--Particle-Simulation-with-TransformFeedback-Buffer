#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <vector>


#include "constants.h"
#include "Shader.h"
#include "Particle.h"
#include "Camera.h"
#include "Mouse.h"

using namespace std; 
class SDLGLProgram
{

public:
  SDLGLProgram(int w, int h);
  ~SDLGLProgram();

  void loop();

private:
  vector<Particle> particles;
  GLuint VAO, VBO; 
  Camera camera;
  Mouse *mouse; 
  Shader *shader; 

  int screenHeight, screenWidth;
  SDL_Window *window;
  SDL_GLContext context;

  void update();
  void render();
  void initBufferData(); 
  /**
   * call this function every time the particles are updated, to buffer updated particles to GPU
   */
  void _bufferParticles(); 
  /**
   * Generates VAO and VBO, this function should be only triggered once 
   */
  void _genBuffers(); 
  void _delBuffers(); 

  void printParticles(); // print the first 10 particles for testing purposes

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
