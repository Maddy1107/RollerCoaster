#version 400 core

struct LightInfo
{
	vec4 position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
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


uniform LightInfo Spherelight; 
//uniform LightInfo light2; 
uniform MaterialInfo material1; 

// Layout of vertex attributes in VBO
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;
layout (location = 2) in vec3 inNormal;

flat out vec3 vColour;


out vec3 reflectedVector;
uniform vec3 cam_position;

out float visibility;


// This function implements the Phong shading model
// The code is based on the OpenGL 4.0 Shading Language Cookbook, Chapter 2, pp. 62 - 63, with a few tweaks. 
// Please see Chapter 2 of the book for a detailed discussion.
vec3 PhongModel(vec4 p, vec3 n)
{
	vec3 s = normalize(vec3(Spherelight.position - p));
	vec3 v = normalize(-p.xyz);
	vec3 r = reflect(-s, n);
	vec3 h = normalize(v + s);
	vec3 ambient = Spherelight.La * material1.Ma;
	float sDotN = max(dot(s, n), 0.0);
	vec3 diffuse = Spherelight.Ld * material1.Md * sDotN;
	vec3 specular = vec3(0.0);
	if (sDotN > 0.0)
		specular = Spherelight.Ls * material1.Ms * pow(max(dot(h, n), 0.0), material1.shininess);
	
	return ambient + diffuse + specular;

}

void main()
{	

	// Transform the vertex spatial position using the projection and modelview matrices
	gl_Position = matrices.projMatrix * matrices.modelViewMatrix * vec4(inPosition, 1.0);
	
	// Get the vertex normal and vertex position in eye coordinates
	vec3 n = normalize(matrices.normalMatrix * inNormal);
	vec4 p = matrices.modelViewMatrix * vec4(inPosition, 1.0f);

	vColour = PhongModel(p,n);

	vec3 ViewVector = normalize(inPosition - cam_position);
	reflectedVector = reflect(ViewVector, inNormal);

	float distanceFromCam = length(p.xyz);
	visibility = exp(-0.007 * distanceFromCam);
	visibility = clamp(visibility,0.0,1.0);
	
} 

