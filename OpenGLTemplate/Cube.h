#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"

// Class for generating a xz plane of a given size
class CCube
{
public:
	CCube();
	~CCube();
	void Create(string sDirectory, string sFilename, float fWidth, float fHeight, float breadth, float fTextureRepeat);
	void Render();
	void Release();
private:
	UINT m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_texture;
	string m_directory;
	string m_filename;
	float m_length;
	float m_breadth;
	float m_height;
};