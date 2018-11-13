#include "Image.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <memory>

Image::Image(std::string filepath) : m_filepath(filepath){
	std::cout << "(Image.h) Constructor called\n";    
}


// Destructor
Image::~Image (){
    // Delete our pixel data.	
    // Note: We could actually do this sooner
    // in our rendering process.
    if(m_PixelData!=NULL){
        delete[] m_PixelData;
    }
}

// Little function for loading the pixel data
// from a PPM image.
// TODO: Expects a very specific version of PPM!
//
// flip - Will flip the pixels upside down in the data
//        If you use this be consistent.
void Image::loadPPM(bool flip){

  // Open an input file stream for reading a file
  std::ifstream ppmFile(m_filepath.c_str());
  // If our file successfully opens, begin to process it.
  if (ppmFile.is_open()){
      // line will store one line of input
      std::string line;
      // Our loop invariant is to continue reading input until
      // we reach the end of the file and it reads in a NULL character
      std::cout << "Reading in ppm file: " << m_filepath << std::endl;
      unsigned int iteration = 0;
      unsigned int pos = 0;
      while ( getline (ppmFile,line) ){
         if(line[0]=='P'){
            magicNumber = line;
         }else if(iteration==1){
            // Returns first token 
            char *token = strtok((char*)line.c_str(), " "); 
            m_width = atoi(token);
            token = strtok(NULL, " ");
            m_height = atoi(token);
            std::cout << "PPM width,height=" << m_width << "," << m_height << "\n";	
            if(m_width > 0 && m_height > 0){
                m_PixelData = new unsigned char[m_width*m_height*3];
                if(m_PixelData==NULL){
                    std::cout << "Unable to allocate memory for ppm" << std::endl;
                    exit(1);
                 }
             }else{
                std::cout << "PPM not parsed correctly, width and/or height dimensions are 0" << std::endl;
                exit(1);
             }
         }else if(iteration==2){
            // max color range is stored here
            // TODO: Can be stored optionally
         }else{
            m_PixelData[pos] = (unsigned char)atoi(line.c_str());
            ++pos;
         }
          iteration++;
    }             
    ppmFile.close();
  }
  else{
      std::cout << "Unable to open ppm file:" << m_filepath << std::endl;
  } 

    // Flip all of the pixels
    if(flip){
        // Copy all of the data to a temporary stack-allocated array
        unsigned char* copyData = new unsigned char[m_width*m_height*3];
        for(int i =0; i < m_width*m_height*3; ++i){
            copyData[i]=m_PixelData[i];
        }
        //memcpy(copyData,m_PixelData,(m_width*m_height*3)*sizeof(unsigned char));
        unsigned int pos = (m_width*m_height*3)-1;
        for(int i =0; i < m_width*m_height*3; i+=3){
            m_PixelData[pos]=copyData[i+2];
            m_PixelData[pos-1]=copyData[i+1];
            m_PixelData[pos-2]=copyData[i];
            pos-=3;
        }
        delete[] copyData;
    }


}

/*  ===============================================
Desc: Sets a pixel in our array a specific color
Precondition: 
Post-condition:
=============================================== */ 
void Image::setPixel(int x, int y, int r, int g, int b){
  if(x > m_width || y > m_height){
    return;
  }
  else{
    /*std::cout << "modifying pixel at " 
              << x << "," << y << "from (" <<
              (int)color[x*y] << "," << (int)color[x*y+1] << "," <<
(int)color[x*y+2] << ")";*/

    m_PixelData[(x*3)+m_height*(y*3)] = r;
    m_PixelData[(x*3)+m_height*(y*3)+1] = g;
    m_PixelData[(x*3)+m_height*(y*3)+2] = b;

/*    std::cout << " to (" << (int)color[x*y] << "," << (int)color[x*y+1] << ","
<< (int)color[x*y+2] << ")" << std::endl;*/

  }
}

/*  ===============================================
Desc: 
Precondition: 
Post-condition:
=============================================== */ 
void Image::printPixels(){
    for(int x = 0; x <  m_width*m_height*3; ++x){
        std::cout << " " << (int)m_PixelData[x];
    }
    std::cout << "\n";
}

/*  ===============================================
Desc: Returns pixel data for our image
Precondition: 
Post-condition:
=============================================== */ 
unsigned char* Image::getPixelData(){
    return m_PixelData;
}
