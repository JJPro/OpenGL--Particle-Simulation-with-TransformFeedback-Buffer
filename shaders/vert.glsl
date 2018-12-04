#version 330 core

layout(location=0)in vec2 acceleration; // determines frag color
layout(location=1)in vec2 speed;        // place for improvement: currently speed is not used in shaders
layout(location=2)in vec2 pos; 

uniform mat3 camMatrix; 

out VS_OUT
{
	vec2 acceleration; 
} vs_out; 

void main()
{
	gl_Position = vec4(camMatrix * vec3(pos, 0), 1); 
	// gl_PointSize = 10.0; 

	vs_out.acceleration = acceleration; 
}