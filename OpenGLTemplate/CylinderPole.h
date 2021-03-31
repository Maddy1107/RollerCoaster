#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"

// Class for generating a xz plane of a given size
class CCylinder
{
public:
	CCylinder();
	~CCylinder();
	void TextureLoad(string directory, string filename);
	void Create(float height, float radius, float textureRepeat);
	void Calculate(float height, string pos);
	void Render();
	void Release();
	void BufferAttribFunc(GLuint VAO);
	void BufferObjectFunc(CVertexBufferObject VBO);
	void VAOUploadToGPU(CVertexBufferObject VBO);
private:
	UINT m_vaoTop;
	UINT m_vaoBase;
	UINT m_vaoBody;
	CVertexBufferObject m_vboTop;
	CVertexBufferObject m_vboBase;
	CVertexBufferObject m_vboBody;

	CTexture m_texture;
	string m_directory;
	string m_filename;
	float m_radius;
	float m_height;
	vector<glm::vec3> vertTop;
	vector<glm::vec3> vertBase;

	unsigned int m_vertexCount;

};