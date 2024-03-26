#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Logger.h"

Texture::Texture(std::string filename)
{
	int width, height, channelCount;

	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channelCount, 0);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	switch (channelCount)
	{
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		break;

	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		break;

	default:
		Logger::Log({ "Textures using ", std::to_string(channelCount), " colour channels are not supported" }, LogType::Warning);
		break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(imageData);
}

void Texture::BindBuffer(int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::UnbindBuffer(int textureIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	if (IsValid())
	{
		glDeleteTextures(1, &m_textureID);
	}
}
