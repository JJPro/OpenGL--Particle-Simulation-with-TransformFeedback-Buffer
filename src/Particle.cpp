#include "Particle.h"

void Particle::update(Mouse &mouse, mat3 camMatrix)
{
    // acceleration 
    if (mouse.isMouseDown()){
        // cout << "mouse down detected, changing acceleration" << endl;
        vec2 mousePos = mouse.getMousePosInLocalCoord(camMatrix);
        vec2 direction_vec = mousePos - pos;
        float dist = length(direction_vec);

        // magnitude of acceleration
        float modulus = GRAVITATIONAL_CONSTANT / (dist * dist); // magnitude of new acceleration
        if (modulus > PARTICLE_ACCELERATION_MAX) modulus = PARTICLE_ACCELERATION_MAX; // constraint acceleration
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
    // limit speed to maximum of 0.3
    if (length(speed) > 0.3) speed = normalize(speed) * vec2(0.3); 

    /**
     * Bounds Check 
     * 
     * If particle hit the boundary, it should bounce back: 
     *      - pos no change 
     *      - speed = mirror speed to the bounding border 
     *      - acceleration = resistence force in speed's opposite direction, iff mouse is not down
     *                          if mouse is down, we don't care then. 
     */

    float tmp = ((float)BOX_EDGE_LEN) / 2;
    vec4 boxBounds = vec4(vec2(-tmp, tmp),  // up-left corner
                          vec2(tmp, -tmp)); // bottom-right corner
    // cout << "bounds check: " << to_string(boxBounds) << endl;

    vec2 potentialPos = pos + speed; 
    bool hitBounds = false; 
    if (potentialPos.x < boxBounds.x || potentialPos.x > boxBounds.z) // hits left or right boundaries
    {
        speed.x = -speed.x; 
        hitBounds = true; 
    }
    if (potentialPos.y < boxBounds.w || potentialPos.y > boxBounds.y) // hits top or bottom boundaries
    {
        speed.y = -speed.y;
        hitBounds = true;
    }
    
    // pos
    if (!hitBounds)
        pos += speed;

    if (!mouse.isMouseDown() && length(speed))
        acceleration = normalize(-speed) * PARTICLE_MOVING_RESISTENCE;

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