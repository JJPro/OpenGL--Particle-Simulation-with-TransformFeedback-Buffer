#version 330 core

out vec4 fragColor;

uniform float PARTICLE_ACCELERATION_MAX; 

in VS_OUT
{
	vec2 acceleration; 
	vec2 speed;
} fs_in; 

void main()
{
	/** Description: 
	 *
	 * Particle color depends on acceleration 
	 * 	The bigger the acceleration, the smaller its g component
	 *       (the amount of green affects the gradient of red to revail against yellow)
	 */
	
	// calculate magnitude/modulus of acceleration vector
	float modulus = length(fs_in.acceleration); 
	const float MAX_GREEN = 0.9f; 
	const float MIN_GREEN = 0.3f; 
	float g = (1 - modulus / PARTICLE_ACCELERATION_MAX) * (MAX_GREEN - MIN_GREEN) + MIN_GREEN; 
	fragColor = vec4(0.906, g, 0.2, 1);
}
