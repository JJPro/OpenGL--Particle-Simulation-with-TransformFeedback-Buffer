#version 330 core

layout(location=0)in vec2 acceleration; // determines frag color
layout(location=1)in vec2 speed;        // place for improvement: currently speed is not used in shaders
layout(location=2)in vec2 pos; 

out vec2 outAcceleration; 
out vec2 outSpeed; 
out vec2 outPos; 

uniform float GRAVITATIONAL_CONSTANT; 
uniform float PARTICLE_ACCELERATION_MAX; 
uniform float PARTICLE_SPEED_MAX; 
uniform float PARTICLE_MOVING_RESISTENCE; 

uniform mat3 camMatrix; 
uniform vec4 boxBounds; 
uniform struct {
	bool isMouseDown; 
	vec2 mousePos; 
} Mouse; 

out VS_OUT
{
	vec2 acceleration; 
	vec2 speed; 
} vs_out; 

void updateParticle(); 

void main()
{
	outPos = pos; 
	// gl_PointSize = 1; 

	updateParticle(); 
	vs_out.acceleration = outAcceleration; 
	vs_out.speed = outSpeed; 

	gl_Position = vec4(camMatrix * vec3(outPos, 1), 1); 
}

void updateParticle()
{
	// acceleration
	if (Mouse.isMouseDown) {
		vec2 dir = Mouse.mousePos - pos; 
		float dist = length(dir); 

        // magnitude of acceleration
        float modulus = GRAVITATIONAL_CONSTANT / (dist * dist); // magnitude of new acceleration
        if (modulus > PARTICLE_ACCELERATION_MAX) modulus = PARTICLE_ACCELERATION_MAX; // constraint acceleration
        outAcceleration = normalize(dir) * modulus; 
	} else {
		if (length(speed) > 0)
            outAcceleration = normalize(-speed) * PARTICLE_MOVING_RESISTENCE; // resistence acceleration in reverse moving direction to slow it down
        else 
            outAcceleration = vec2(0); 
	}

	// speed
	if (Mouse.isMouseDown){
        outSpeed = speed + outAcceleration; 
    } else {
        // make sure speed won't autodecay too much pass 0 
        if (dot(speed, speed+outAcceleration) < 0){
            outSpeed = outAcceleration = vec2(0); 
        } else {
			outSpeed = speed + outAcceleration; 
        }
    }
    // limit speed to maximum of 0.3
    if (length(outSpeed) > PARTICLE_SPEED_MAX)
        outSpeed = normalize(outSpeed) * vec2(PARTICLE_SPEED_MAX);


	/**
     * Bounds Check 
     * 
     * If particle hit the boundary, it should bounce back: 
     *      - pos no change 
     *      - speed = mirror speed to the bounding border 
     *      - acceleration = resistence force in speed's opposite direction, iff mouse is not down
     *                          if mouse is down, we don't care then. 
     */
	vec2 potentialPos = pos + outSpeed; 
    bool hitBounds = false; 
    if (potentialPos.x < boxBounds.x || potentialPos.x > boxBounds.z) // hits left or right boundaries
    {
        outSpeed.x = -outSpeed.x; 
        hitBounds = true; 
    }
    if (potentialPos.y < boxBounds.w || potentialPos.y > boxBounds.y) // hits top or bottom boundaries
    {
        outSpeed.y = -outSpeed.y;
        hitBounds = true;
    }
    
    // pos
    if (!hitBounds)
        outPos = pos + outSpeed;

    if (!Mouse.isMouseDown && length(outSpeed) > 0)
        outAcceleration = normalize(-outSpeed) * PARTICLE_MOVING_RESISTENCE;

}