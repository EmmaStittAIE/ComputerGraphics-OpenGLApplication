#pragma once
#include "GraphicsDef.h"

#include <string>

class ShaderProgram
{
private:
	// These "GLuint"s are essentially just IDs that point toward resources managed by OpenGL
	GLuint m_vertexShader = 0;
	GLuint m_fragmentShader = 0;
	GLuint m_shaderProgram = 0;

	bool m_loadSuccessful = false;

	void DeallocateShaders();

public:
	ShaderProgram() {}
	// Eventually, this needs to allow for optionally not including a shader
	ShaderProgram(std::string vertexFilePath, std::string fragmentFilePath);

	// Removing copy constructors, because they would cause chaos
	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator= (const ShaderProgram& other) = delete;

	// Custom move constructors, because that's okay if we handle it
	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator= (ShaderProgram&& other) noexcept;

	// Getters/Setters	
	bool LoadSuccessful() const { return m_loadSuccessful; }

	void UseShaderProgram();

	void SetUniformInt(std::string uniformName, int value);
	void SetUniformFloat(std::string uniformName, float value);
	void SetUniformVec2(std::string uniformName, float x, float y);
	void SetUniformVec3(std::string uniformName, float x, float y, float z);
	void SetUniformMat4(std::string uniformName, float* matrix);

	~ShaderProgram();
};