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
        acceleration = normalize(-speed) * PARTICLE_MOVING_RESISTENCE; // resistence acceleration in reverse moving direction to slow it down
    }

    // speed 
    if (mouse.isMouseDown()){
        speed += acceleration; 
    } else {
        // make sure speed won't autodecay too much pass 0 
        if (dot(speed, speed+acceleration) < 0){
            speed = acceleration = vec2(0); 
        }
    }

    // pos 
    pos += speed; 
}