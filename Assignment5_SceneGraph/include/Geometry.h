/** @file Geometry.h
 *  @brief Organizes vertex and triangle information.
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

// Purpose of this class is to store vertice and triangle information
class Geometry{
public:
    // Constructor
    Geometry();
    // Destructor
    ~Geometry();
    
    // Functions for working with individual vertices
    unsigned int getSizeInBytes();
    unsigned int getSize();
    float* getData();
    // Manually push back data
    void addVertex(float x, float y, float z);
    void addIndex(unsigned int i);
    void addTexture(float s, float t);	
    // gen pushes all attributes into a single vector
    void gen();
    // Functions for working with Indices
    // Creates a triangle from 3 indicies
    // When a triangle is made, the tangents and bi-tangents are also
    // computed
    void makeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);  

    unsigned int getIndicesSize();
    unsigned int* getIndicesData();

private:
    // All data stores all of the vertexPositons, coordinates, normals, etc.
    // This is all of the information that should be sent to the vertex Buffer Object
    // for instance.
    std::vector<float> allData;

    std::vector<float> vertexPositions;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<float> Tangents;
    std::vector<float> BiTangents;

    // The indices for a indexed-triangle mesh
    std::vector<unsigned int> indices;
};





#endif
