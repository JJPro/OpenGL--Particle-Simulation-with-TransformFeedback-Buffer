#if !defined(CONSTANTS_H)
#define CONSTANTS_H

/**
 * This file holds all the global constants used in our program
 */ 

#define REFRESH_DELAY 20
#define PARTICLE_COUNT 2000000
#define PARTICLE_MOVING_RESISTENCE 0.004f
#define PARTICLE_ACCELERATION_MAX 0.04f
#define PARTICLE_SPEED_MAX 0.2f
#define CAM_SPEED 0.95f
#define BOX_EDGE_LEN 1.8f // bounding box is a square shape, len in OpenGL normalized coord sys
#define GRAVITATIONAL_CONSTANT 0.2f


#endif // CONSTANTS_H