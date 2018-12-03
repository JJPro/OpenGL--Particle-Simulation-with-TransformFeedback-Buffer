#include "Particle.h"

void Particle::update(Mouse &mouse)
{
    // acceleration 
    if (mouse.isMouseDown()){
        vec2 mousePos = mouse.getMousePosNormalized(); 
        vec2 direction_vec = mousePos - pos;
        float dist = length(direction_vec);

        float modulus = GRAVITATIONAL_CONSTANT / (dist * dist); // magnitude of new acceleration
        acceleration = normalize(direction_vec) * modulus; 
    } else {
        acceleration = normalize(-speed) * PARTICLE_MOVING_RESISTENCE;
    }

    // speed 
    speed += acceleration; 

    // pos 
    pos += speed; 
}