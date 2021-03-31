#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"

// Class for generating a xz plane of a given size
class Diamond
{
public:
	Diamond();
	~Diamond();
	void Create(string directory, string filename, float width, float height, float textureRepeat);
	void Render();
	void Release();

private:
	UINT m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_texture;
	string m_directory;
	string m_filename;
	float m_width;
	float m_height;

};