#version 330 core

out vec4 fragColor;

in VS_OUT
{
	vec2 acceleration; 
} fs_in; 

void main()
{
	/** Description: 
	 *
	 * Particle color depends on acceleration 
	 * 	The bigger the acceleration, the bigger its g component
	 *       (the amount of green affects the gradient of red to revail against yellow)
	 */
	
	// calculate magnitude/modulus of acceleration vector
	float modulus = length(fs_in.acceleration); 
	float g = max(1-modulus, 0.9); 
	fragColor = vec4(0.906, g, 0.2, 1);
}
