// ==================================================================
#version 330 core

// The final output color of each 'fragment' from our fragment shader.
out vec4 FragColor;

// Take in our previous texture coordinates.
in vec3 FragPos;
in vec2 v_texCoord;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;


// If we have texture coordinates, they are stored in this sampler.
uniform sampler2D u_DiffuseMap; 
uniform sampler2D u_NormalMap; 

void main()
{
	// Store the texture coordinates
	vec3 normal = texture(u_NormalMap, v_texCoord).rgb;
	vec3 color =  texture(u_DiffuseMap, v_texCoord).rgb;

	if(v_texCoord.y > 0.5){
	    FragColor = vec4(normal,1.0);
	}else{
	    FragColor = vec4(color,1.0);
	}
}
// ==================================================================
