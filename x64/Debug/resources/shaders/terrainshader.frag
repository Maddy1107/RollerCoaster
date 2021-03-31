#version 400 core

uniform float t;

out vec4 vOutputColour;

const int AMOUNT = 12;

in vec3 pos;

in float visibility;
uniform vec3 fogColor;
uniform bool fogEnable;

void main()
{	
    	vec2 coord = 20.0 * (gl_FragCoord.xy - 2000 / 2.0) / 2000;

		float len;

		for (int i = 0; i < AMOUNT; i++)
		{
			len = length(vec2(coord.x, coord.y));

			coord.x = coord.x - cos(coord.y + sin(len)) + cos(t / 9.0);
			coord.y = coord.y + sin(coord.x + cos(len)) + sin(t / 12.0);
		}

		vOutputColour = vec4(cos(len * 2.0), cos(len * 9.0), 0.0, 1.0);

	if(fogEnable)
		vOutputColour = mix(vec4(fogColor,1.0), vOutputColour, visibility);
}
