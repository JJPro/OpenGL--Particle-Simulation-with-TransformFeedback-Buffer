#include "Terrain.h"
#include "Image.h"

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int xSegs, unsigned int zSegs, std::string fileName) : 
                xSegments(xSegs), zSegments(zSegs) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    // Load up some image data
    Image heightMap(fileName);
    heightMap.loadPPM(true);
    // Set the height data for the image
    // TODO: Currently there is a 1-1 mapping between a pixel and a segment
    // You might consider interpolating values if there are more segments
    // than pixels. 
    float scale = 5.0f; // Note that this scales down the values to make
                        // the image a bit more flat.
    // Create height data
    heightData = new int[xSegments*zSegments];
    // Set the height data equal to the grayscale value of the heightmap
    // Because the R,G,B will all be equal in a grayscale iamge, then
    // we just grab one of the color components.
    for(unsigned int z = 0 ; z < zSegments; ++z){
        for(unsigned int x = 0; x < xSegments; ++x){
            heightData[x+z*xSegments] = (float)heightMap.getPixelR(z,x)/scale;
        }
    }
    init();
}

// Destructor
Terrain::~Terrain(){
    if(heightData!=nullptr){
        delete heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void Terrain::init(){
    // Create the initial grid of vertices.
    for(unsigned int z =0 ; z < zSegments; ++z){
        for(unsigned int x = 0; x < xSegments; ++x){
            // z is negative so we build the heightmap 'away' from the camera
            geometry.addVertex(x,heightData[x+z*xSegments],z);   // Position
            // Calculate the texture
            float u = 1.0f - ((float)x/(float)xSegments);
            float v = 1.0f - ((float)z/(float)zSegments);
            geometry.addTexture(u,v);    // Texture
        }
    }

    // Figure out which indices make up each triangle
    // By writing out a few of the indicies you can figure out
    // the pattern here. Note there is an offset.
     for(unsigned int z =0 ; z < zSegments-1; ++z){
        for(unsigned int x = 0; x < xSegments-1; ++x){
           geometry.addIndex(x+(z*zSegments));
           geometry.addIndex(x+(z*zSegments)+xSegments);
           geometry.addIndex(x+(z*zSegments)+1);

           geometry.addIndex(x+(z*zSegments)+1);
           geometry.addIndex(x+(z*zSegments)+xSegments);
           geometry.addIndex(x+(z*zSegments)+xSegments+1);
        }
    }

   // Finally generate a simple 'array of bytes' that contains
   // everything for our buffer to work with.
   geometry.gen();  
   // Create a buffer and set the stride of information
   myBuffer.CreateBufferNormalMapLayout(14,
                                            geometry.getSize(),
                                            geometry.getIndicesSize(),
                                            geometry.getData(),
                                            geometry.getIndicesData());

}

// Loads an image and uses it to set the heights of the terrain.
void Terrain::loadHeightMap(Image image){

}
