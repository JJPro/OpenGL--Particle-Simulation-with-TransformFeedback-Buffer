/** @file Image.h
 *  @brief Sets up an OpenGL camera..
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
public:
    Image (std::string filepath);

    ~Image();

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
    // Retrieve raw array of pixel data
    unsigned char* getPixelData();

private:
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
