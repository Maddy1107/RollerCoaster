#version 400 core

// Structure for matrices
uniform struct Matrices
{
	mat4 projMatrix;
	mat4 modelViewMatrix; 
	mat3 normalMatrix;
} matrices; 

// Layout of vertex attributes in VBO
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;

out float visibility;
out vec3 pos;

void main()
{	

	// Normally, one would simply transform the vertex spatial position using 
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition, 1.0);
	
	vec4 vEyePosition = matrices.modelViewMatrix * vec4(inPosition, 1.0f);

	pos = inPosition;

	float distanceFromCam = length(vEyePosition.xyz);
	visibility = exp(-0.007 * distanceFromCam);
	visibility = clamp(visibility,0.0,1.0);
} 
