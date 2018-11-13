/** @file Buffer.h
 *  @brief Sets up a variety of Vertex Buffer Object (VBO) layouts.
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef BUFFER_H
#define BUFFER_H

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>


class Buffer{ 
public:
    // Generates a new buffer
    Buffer();
    // Destroys all of our buffers.
    ~Buffer();
    // Selects the buffer to bind
    // We only need to bind to a buffer
    // again if we are updating the data.
    void Bind();
    // Unbind our buffers
    void Unbind();
    // vcount: the number of vertices
    // icount: the number of indices
    // vdata: A pointer to an array of data for vertices
    // idata: A pointer to an array of data for indices
    void CreateBufferLayout(unsigned int stride,unsigned int vcount,unsigned int
icount, float* vdata, unsigned int* idata );
    // vcount: the number of vertices
    // icount: the number of indices
    // vdata: A pointer to an array of data for vertices
    // idata: A pointer to an array of data for indices
    void CreateBufferTextureLayout(unsigned int stride,unsigned int vcount,unsigned int
icount, float* vdata, unsigned int* idata );
    // vcount: the number of vertices
    // icount: the number of indices
    // vdata: A pointer to an array of data for vertices
    // idata: A pointer to an array of data for indices
    void CreateBufferNormalMapLayout(unsigned int stride,unsigned int vcount,unsigned int
icount, float* vdata, unsigned int* idata );

private:

    // Vertex Array Object
    GLuint m_VAOId;
    // Vertex Buffer
    GLuint m_vertexPositionBuffer;
    // Index Buffer Object
    GLuint m_indexBufferObject;
    // Stride of data (how do I get to the next vertex
    unsigned int m_stride{0};

};


#endif
