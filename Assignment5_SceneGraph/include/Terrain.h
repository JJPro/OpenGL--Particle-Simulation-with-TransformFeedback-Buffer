/** @file Terrain.h
 *  @brief Create a terrain
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TERRAIN_H
#define TERRAIN_H

#include "Texture.h"
#include "Shader.h"
#include "Image.h"
#include <vector>

class Terrain {
public:
    Terrain (unsigned int xSegs, unsigned int ySegs);
    ~Terrain ();

    // Loads a heightmap based on a PPM image
    void loadHeightMap(Image image);

private:
    /* data */
    unsigned int xSegments;
    unsigned int ySegments;

    // Textures for the terrain
    std::vector<Texture> textures;
    // Shader for the terrain
    Shader myShader;
};

#endif
