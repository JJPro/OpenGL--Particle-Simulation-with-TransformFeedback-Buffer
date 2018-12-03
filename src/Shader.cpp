#include "Shader.h"

Shader::Shader(std::string vShaderPath, std::string fShaderPath)
{
  std::string vertexCode, fragmentCode;
  std::ifstream vShaderFile, fShaderFile;

  // ensure ifstream objects throws
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    vShaderFile.open(vShaderPath);
    fShaderFile.open(fShaderPath);

    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    // compile shaders
    unsigned int vertexShader, fragmentShader;
    vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // link shaders in the program
    glLinkProgram(ID);
    glValidateProgram(ID);

    // Once the shaders have been liked in, we can delete them.
    glDetachShader(ID, vertexShader);
    glDetachShader(ID, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // print linking errors if any
    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
      std::cout << "ERROR, shader did not link!" << '\n';
    }
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << '\n';
  }
}

Shader::~Shader()
{
  glDeleteProgram(ID);
}

void Shader::use()
{
  glUseProgram(ID);
}

unsigned int Shader::compileShader(unsigned int type, const char *code)
{
  unsigned int id;
  if (type == GL_VERTEX_SHADER)
  {
    id = glCreateShader(GL_VERTEX_SHADER);
  }
  else if (type == GL_FRAGMENT_SHADER)
  {
    id = glCreateShader(GL_FRAGMENT_SHADER);
  }
  glShaderSource(id, 1, &code, NULL);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *errorMessages = new char[length]; // Could also use alloca here.
    glGetShaderInfoLog(id, length, &length, errorMessages);
    if (type == GL_VERTEX_SHADER)
    {
      std::cout << "ERROR: GL_VERTEX_SHADER compilation failed!\n"
                << errorMessages << "\n";
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
      std::cout << "ERROR: GL_FRAGMENT_SHADER compilation failed!\n"
                << errorMessages << "\n";
    }
    // Reclaim our memory
    delete[] errorMessages;
    // Delete our broken shader
    glDeleteShader(id);
    return 0;
  }
  return id;
}

void Shader::setUniform(const GLchar *name, const glm::mat4 &mat)
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setUniform(const GLchar *name, const GLfloat *value)
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, value);
}
void Shader::setUniform(const GLchar *name, float v0, float v1, float v2)
{
  glUniform3f(glGetUniformLocation(ID, name), v0, v1, v2);
}
void Shader::setUniform(const GLchar *name, int value)
{
  glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::setUniform(const GLchar *name, float value)
{
  glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::setUniform(const GLchar *name, const glm::vec3 &vector)
{
  glUniform3fv(glGetUniformLocation(ID, name), 1, &vector[0]); 
}
