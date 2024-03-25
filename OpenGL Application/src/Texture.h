#pragma once

#include <string>

#include "GraphicsDef.h"

class Texture
{
private:
	GLuint m_textureID = 0;

public:
	Texture() = default;
	Texture(std::string filename);

	void BindBuffer(int textureIndex) const;
	static void UnbindBuffer(int textureIndex);

	bool IsValid() const { return m_textureID != 0; }

	~Texture();
};