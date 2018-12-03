#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // use glad to get all the required OpenGL headers
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
  // the program ID
  unsigned int ID;

  // constructor reads and builds the shader
  Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
  ~Shader();
  // use/activate the shader
  void use();
  // set uniforms for our shader.
  void setUniform(const GLchar *name, const glm::mat4 &);
  void setUniform(const GLchar *name, const GLfloat *);
  void setUniform(const GLchar *name, float, float, float);
  void setUniform(const GLchar *name, int);
  void setUniform(const GLchar *name, float);
  void setUniform(const GLchar *name, const glm::vec3 &);

private:
  unsigned int compileShader(unsigned int type, const char *code);
};

#endif
