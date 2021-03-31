#version 400 core

struct LightInfo
{
	vec4 position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
	vec3 direction;
	float exponent;
	float cutoff;
};


struct MaterialInfo
{
	vec3 Ma;
	vec3 Md;
	vec3 Ms;
	float shininess;
};

// Structure for matrices
uniform struct Matrices
{
	mat4 projMatrix;
	mat4 modelViewMatrix; 
	mat3 normalMatrix;
} matrices;

uniform LightInfo light2; 
uniform MaterialInfo material2; 
uniform LightInfo light3; 
uniform MaterialInfo material3; 

// Layout of vertex attributes in VBO
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;

out vec3 vColour;

out vec2 vTexCoord;	// Texture coordinate

out float visibility;

vec3 BlinnPhongSpotlightModel(LightInfo light, vec4 p, vec3 n, MaterialInfo material)
{
	vec3 s = normalize(vec3(light.position - p));
	float angle = acos(dot(-s, light.direction));
	float cutoff = radians(clamp(light.cutoff, 0.0, 90.0));
	vec3 ambient = light.La * material.Ma;
	if (angle < cutoff) {
		float spotFactor = pow(dot(-s, light.direction), light.exponent);
		vec3 v = normalize(-p.xyz);
		vec3 h = normalize(v + s);
		float sDotN = max(dot(s, n), 0.0);
		vec3 diffuse = light.Ld * material.Md * sDotN;
		vec3 specular = vec3(0.0);
		if (sDotN > 0.0)
			specular = light.Ls * material.Ms * pow(max(dot(h, n), 0.0), material.shininess);
		return ambient + spotFactor * (diffuse + specular);
	} else 
		return ambient;
}

void main()
{	

	// Transform the vertex spatial position using the projection and modelview matrices
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition, 1.0);
	
	// Get the vertex normal and vertex position in eye coordinates
	vec3 n = normalize(matrices.normalMatrix * inNormal);
	vec4 p = matrices.modelViewMatrix * vec4(inPosition, 1.0f);

	vColour = BlinnPhongSpotlightModel (light2, p, normalize(n),material2);

	vTexCoord = inCoord;

	float distanceFromCam = length(p.xyz);
	visibility = exp(-0.007 * distanceFromCam);
	visibility = clamp(visibility,0.0,1.0);
} 

