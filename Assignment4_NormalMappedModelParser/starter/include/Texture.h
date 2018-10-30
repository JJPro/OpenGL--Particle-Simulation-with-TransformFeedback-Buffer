#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <memory>

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
	// Loads a PPM from memory.
	void loadPPM(bool flip);
    // Return the width
    inline int getWidth(){
        return m_width;
    }
    // Return the height
    inline int getHeight(){
        return m_height;
    }
    // Bytes per pixel
    inline int getBPP(){
        return m_BPP;
    }
    // Set a pixel a particular color in our data
    void setPixel(int x, int y, int r, int g, int b);
    // Display the pixels
    void printPixels();

private:
    // Store a unique ID for the texture
    GLuint m_TextureID;
	// Filepath to the image loaded
    std::string m_filepath;
	// Raw pixel data
    unsigned char* m_PixelData;
	// Size and format of image
    int m_width{0}; // Width of the image
    int m_height{0}; // Height of the image
    int m_BPP{0};   // Bits per pixel (i.e. how colorful are our pixels)
	std::string magicNumber; // magicNumber if any for image format

};



#endif
