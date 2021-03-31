#version 400 core 

flat in vec3 vColour;

out vec4 vOutputColour;

in vec3 reflectedVector;

uniform samplerCube cubeMap;
uniform bool fogEnable;
in float visibility;
uniform vec3 fogColor;
void main()
{	
	vOutputColour = vec4(vColour, 1.0);	

	vec4 reflectedColor = texture(cubeMap, reflectedVector);

	vOutputColour = mix(vOutputColour, reflectedColor, 1);

	if(fogEnable)
		vOutputColour = mix(vec4(fogColor,1.0), vOutputColour, visibility);
}
