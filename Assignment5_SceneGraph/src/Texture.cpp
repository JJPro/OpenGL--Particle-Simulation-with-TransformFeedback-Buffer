#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


#include "Texture.h"
#include <glad/glad.h>

// Default Constructor
Texture::Texture(){

}


// Default Destructor
Texture::~Texture(){
   // Delete our texture from the GPU
   glDeleteTextures(1,&m_TextureID);
}

void Texture::LoadTexture(const std::string filepath){
    // Set member variable
    m_filepath = filepath;
    // Load our actual image data
    // This method loads .ppm files of pixel data
    m_image = new Image(filepath);
    m_image->loadPPM(true);

    glEnable(GL_TEXTURE_2D); 
    // Generate a buffer for our texture
    glGenTextures(1,&m_TextureID);
    // Similar to our vertex buffers, we now 'select'
    // a texture we want to bind to.
    // Note the type of data is 'GL_TEXTURE_2D'
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    // Now we are going to setup some information about
    // our textures.
    // There are four parameters that must be set.
    // GL_TEXTURE_MIN_FILTER - How texture filters (linearly, etc.)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    // Wrap mode describes what to do if we go outside the boundaries of
    // texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    // At this point, we are now ready to load and send some data to OpenGL.
    glTexImage2D(GL_TEXTURE_2D,
                            0 ,
                        GL_RGB,
                        m_image->getWidth(),
                        m_image->getHeight(),
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        m_image->getPixelData()); // Here is the raw pixel data
    // We are done with our texture data so we can unbind.
    // Generate a mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // Un-select our texture
    glBindTexture(GL_TEXTURE_2D, 0);

    delete m_image;
}




// slot tells us which slot we want to bind to.
// We can have multiple slots. By default, we
// will set our slot to 0 if it is not specified.
void Texture::Bind(unsigned int slot) const{
	// Using OpenGL 'state' machine we set the active texture
	// slot that we want to occupy. Again, there could
	// be multiple at once.
	// At the time of writing, OpenGL supports 8-32 depending
	// on your hardware.
    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}


