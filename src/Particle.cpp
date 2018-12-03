#include "Particle.h"

void Particle::update(Mouse &mouse)
{
    // acceleration 
    if (mouse.isMouseDown()){
        // cout << "mouse down detected, changing acceleration" << endl;
        vec2 mousePos = mouse.getMousePosNormalized(); 
        vec2 direction_vec = mousePos - pos;
        float dist = length(direction_vec);

        // magnitude of acceleration
        float modulus = GRAVITATIONAL_CONSTANT / (dist * dist); // magnitude of new acceleration
        acceleration = normalize(direction_vec) * modulus; 
        // cout << "dist = " << dist << endl;
        // cout << "acceleration modulus = " << modulus << endl;
        // cout << "acceleration caused by force is " << to_string(acceleration) << endl;
    } else {
        if (length(speed))
            acceleration = normalize(-speed) * PARTICLE_MOVING_RESISTENCE; // resistence acceleration in reverse moving direction to slow it down
        else 
            acceleration = vec2(0); 
    }

    // speed 
    if (mouse.isMouseDown()){
        speed += acceleration; 
    } else {
        // make sure speed won't autodecay too much pass 0 
        if (dot(speed, speed+acceleration) < 0){
            speed = acceleration = vec2(0); 
        } else {
            speed += acceleration; 
        }
    }

    // pos 
    pos += speed; 
}

string Particle::toString()
{
    static stringstream ss;
    ss.str("");
    ss << "Particle {" << endl; 
    ss << "\t acceleration: " << to_string(acceleration) << endl;
    ss << "\t speed: " << to_string(speed) << endl;
    ss << "\t pos: " << to_string(pos) << endl;
    ss << "}" << endl;; 
    return ss.str(); 
}