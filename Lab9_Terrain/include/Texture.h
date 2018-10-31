/** @file Texture.h
 *  @brief Loads an image and creates an OpenGL texture on the GPU..
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Image.h"

#include <string>
#include <glad/glad.h>

class Texture{
public:
    // Constructor
    Texture();
    // Destructor
    ~Texture();
    // Loads and sets up an actual texture
    void LoadTexture(const std::string filepath);
    // slot tells us which slot we want to bind to.
    // We can have multiple slots. By default, we
    // will set our slot to 0 if it is not specified.
    void Bind(unsigned int slot=0) const;
    // Be done with our texture
    void Unbind();
private:
    // Store a unique ID for the texture
    GLuint m_TextureID;
    // Filepath to the image loaded
    std::string m_filepath;
    // PPM Image
    Image* m_image;

};



#endif
