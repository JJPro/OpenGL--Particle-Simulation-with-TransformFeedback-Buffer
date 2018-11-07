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

#include "Object.h"
#include "Texture.h"
#include "Shader.h"
#include "Image.h"
#include <vector>
#include <string>

class Terrain : public Object {
public:
    // Takes in a Terrain and a filename for the heightmap.
    Terrain (unsigned int xSegs, unsigned int zSegs, std::string fileName);
    ~Terrain ();
    // override the initilization routine.
    void init();
    // Loads a heightmap based on a PPM image
    // This then sets the heights of the terrain.
    void loadHeightMap(Image image);

private:
    // data
    unsigned int xSegments;
    unsigned int zSegments;

    // Store the height in a multidimensional array
    int* heightData;

    // Textures for the terrain
    // Terrains are often 'multitextured' and have multiple textures.
    std::vector<Texture> textures;
};

#endif
