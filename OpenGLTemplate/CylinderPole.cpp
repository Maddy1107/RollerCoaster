#include "Common.h"
#include "CylinderPole.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))


CCylinder::CCylinder()
{}

CCylinder::~CCylinder()
{}

void CCylinder::TextureLoad(string directory, string filename)
{
	// Load the texture
	m_texture.Load(directory + filename, true);

	// Set parameters for texturing using sampler object
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// Create the plane, including its geometry, texture mapping, normal, and colour
void CCylinder::Create(float height, float radius, float textureRepeat)
{
	m_height = height;
	m_radius = radius;

	float halfHeight = m_height / 2.0f;

	// Texture coordinates
	glm::vec2 shapeTexCoords[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(textureRepeat, textureRepeat),
		glm::vec2(textureRepeat, 0.0f),
	};
	glm::vec2 BaseTopTexCoords[4] =
	{
		glm::vec2(0.5f, textureRepeat),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(textureRepeat, 0.0f),
	};

	// Plane normal
	glm::vec3 shapeNormal[24] =
	{
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	glGenVertexArrays(1, &m_vaoTop);
	BufferAttribFunc(m_vaoTop);
	BufferObjectFunc(m_vboTop);	
	
	Calculate(halfHeight,"top");

	glm::vec3 shapeVerticesTop[200];

	for (size_t i = 0; i < vertTop.size(); i++)
	{
		shapeVerticesTop[i] = vertTop[i];
		m_vboTop.AddData(&shapeVerticesTop[i], sizeof(glm::vec3));
		m_vboTop.AddData(&BaseTopTexCoords[i % 3], sizeof(glm::vec2));
		m_vboTop.AddData(&shapeNormal[i], sizeof(glm::vec3));
	}
	VAOUploadToGPU(m_vboTop);

	//Base

	glGenVertexArrays(1, &m_vaoBase);
	BufferAttribFunc(m_vaoBase);
	BufferObjectFunc(m_vboBase);

	Calculate(halfHeight, "base");

	glm::vec3 shapeVerticesBase[200];

	for (size_t i = 0; i < vertBase.size(); i++)
	{
		shapeVerticesBase[i] = vertBase[i];
		m_vboBase.AddData(&shapeVerticesBase[i], sizeof(glm::vec3));
		m_vboBase.AddData(&BaseTopTexCoords[i % 3], sizeof(glm::vec2));
		m_vboBase.AddData(&shapeNormal[i], sizeof(glm::vec3));
	}
	VAOUploadToGPU(m_vboBase);

	//Body
	glGenVertexArrays(1, &m_vaoBody);
	BufferAttribFunc(m_vaoBody);
	BufferObjectFunc(m_vboBody);

	for (size_t i = 0; i < vertBase.size(); i++)
	{
		m_vboBody.AddData(&shapeVerticesTop[i], sizeof(glm::vec3));
		m_vboBody.AddData(&shapeTexCoords[i % 2], sizeof(glm::vec2));
		m_vboBody.AddData(&shapeNormal[i], sizeof(glm::vec3));

		m_vboBody.AddData(&shapeVerticesBase[i], sizeof(glm::vec3));
		m_vboBody.AddData(&shapeTexCoords[(i % 2) + 2], sizeof(glm::vec2));
		m_vboBody.AddData(&shapeNormal[i], sizeof(glm::vec3));
		
		m_vertexCount += 2;
	}
	VAOUploadToGPU(m_vboBody);
}

// Render the plane as a triangle strip
void CCylinder::Render()
{
	m_texture.Bind();

	glBindVertexArray(m_vaoTop);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertTop.size());
	glBindVertexArray(m_vaoBase);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertBase.size());
	glBindVertexArray(m_vaoBody);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CCylinder::Calculate(float height, string pos)
{
	const float PI = 3.1415926f;
	float sectorCount = 10;
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;

	for (size_t i = 0; i < sectorCount; i++)
	{
		sectorAngle = i * sectorStep;
		if (pos == "top")
		{
			vertTop.push_back(glm::vec3(0, height, 0));
			vertTop.push_back(glm::vec3(m_radius * cos(sectorAngle), height, m_radius * sin(sectorAngle)));
			vertTop.push_back(glm::vec3(m_radius * cos(sectorStep + sectorAngle), height, m_radius * sin(sectorStep + sectorAngle)));
		}
		else if (pos == "base")
		{
			vertBase.push_back(glm::vec3(0, -height, 0));
			vertBase.push_back(glm::vec3(m_radius * cos(sectorAngle), -height, m_radius * sin(sectorAngle)));
			vertBase.push_back(glm::vec3(m_radius * cos(sectorStep + sectorAngle), -height, m_radius * sin(sectorStep + sectorAngle)));
		}
	}
}

// Release resources
void CCylinder::Release()
{
	m_texture.Release();
	glDeleteVertexArrays(1, &m_vaoTop);
	m_vboTop.Release();
}

void CCylinder::BufferAttribFunc(GLuint VAO)
{
	glBindVertexArray(VAO);
}

void CCylinder::BufferObjectFunc(CVertexBufferObject VBO)
{
	VBO.Create();
	VBO.Bind();
}

void CCylinder::VAOUploadToGPU(CVertexBufferObject VBO)
{
	// Upload the VBO to the GPU
	VBO.UploadDataToGPU(GL_STATIC_DRAW);
	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}