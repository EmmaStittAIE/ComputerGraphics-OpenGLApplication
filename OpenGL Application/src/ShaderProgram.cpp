#include "ShaderProgram.h"

#include <iostream>

#include "Utils.h"
#include "Logger.h"

void ShaderProgram::DeallocateShaders()
{
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_shaderProgram);
}

ShaderProgram::ShaderProgram(std::string vertexFilePath, std::string fragmentFilePath)
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	m_shaderProgram = glCreateProgram();

	std::string vertexContent = Utils::LoadFileToString(vertexFilePath);
	std::string fragmentContent = Utils::LoadFileToString(fragmentFilePath);

	if (vertexContent == "" || fragmentContent == "")
	{
		Logger::Log({ "One or more shaders did not load successfully." }, LogType::Error);
		DeallocateShaders();
		return;
	}
	else
	{
		const char* vertexContentCStr = vertexContent.c_str();
		const char* fragmentContentCStr = fragmentContent.c_str();

		GLchar errorLog[512];
		GLint success = 0;

		glShaderSource(m_vertexShader, 1, &vertexContentCStr, nullptr);
		glCompileShader(m_vertexShader);

		glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_vertexShader, 512, nullptr, errorLog);
			Logger::Log({ "Vertex shader at \"", vertexFilePath, "\" failed to compile with error:\n", errorLog }, LogType::Error);

			DeallocateShaders();
			return;
		}
		else
		{
			Logger::Log({ "Vertex shader compiled successfully" }, LogType::Info);
		}

		glShaderSource(m_fragmentShader, 1, &fragmentContentCStr, nullptr);
		glCompileShader(m_fragmentShader);

		glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_fragmentShader, 512, nullptr, errorLog);
			Logger::Log({ "Fragment shader at \"", vertexFilePath, "\" failed to compile with error:\n", errorLog }, LogType::Error);
			DeallocateShaders();
			return;
		}
		else
		{
			Logger::Log({ "Fragment shader compiled successfully" }, LogType::Info);
		}

		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);
		glLinkProgram(m_shaderProgram);
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_shaderProgram, 512, nullptr, errorLog);
			Logger::Log({ "Shader program failed to link with error:\n", errorLog }, LogType::Error);
			DeallocateShaders();
			return;
		}
	}

	m_loadSuccessful = true;
	Logger::Log({ "Shader program compiled and linked successfully" }, LogType::Info);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	this->m_shaderProgram = other.m_shaderProgram;
	this->m_fragmentShader = other.m_fragmentShader;
	this->m_vertexShader = other.m_vertexShader;
	this->m_loadSuccessful = other.m_loadSuccessful;

	// Stops other from deallocating our copied shaders
	other.m_loadSuccessful = false;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	// Do nothing if other is ourself
	if (&other == this)
	{
		return *this;
	}

	// If this shader is being replaced by a new shader, then we need to free the current resources
	if (m_loadSuccessful)
	{
		DeallocateShaders();
	}

	this->m_shaderProgram = other.m_shaderProgram;
	this->m_fragmentShader = other.m_fragmentShader;
	this->m_vertexShader = other.m_vertexShader;
	this->m_loadSuccessful = other.m_loadSuccessful;

	// Stops other from deallocating our copied shaders
	other.m_loadSuccessful = false;
	return *this;
}

void ShaderProgram::UseShaderProgram()
{
	glUseProgram(m_shaderProgram);
}

void ShaderProgram::SetUniformInt(std::string uniformName, int value)
{
	GLint uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	if (uniformLocation == -1)
	{
		Logger::Log({ "Uniform \"", uniformName, "\" does not exist."}, LogType::Error);
		return;
	}

	glUniform1i(uniformLocation, value);
}

void ShaderProgram::SetUniformFloat(std::string uniformName, float value)
{
	GLint uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	if (uniformLocation == -1)
	{
		Logger::Log({ "Uniform \"", uniformName, "\" does not exist." }, LogType::Error);
	}
	
	glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetUniformVec2(std::string uniformName, float x, float y)
{
	GLint uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	if (uniformLocation == -1)
	{
		Logger::Log({ "Uniform \"", uniformName, "\" does not exist." }, LogType::Error);
	}
		
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniformVec3(std::string uniformName, float x, float y, float z)
{
	GLint uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	if (uniformLocation == -1)
	{
		Logger::Log({ "Uniform \"", uniformName, "\" does not exist." }, LogType::Error);
	}
	
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniformMat4(std::string uniformName, float* matrix)
{
	GLint uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName.c_str());
	if (uniformLocation == -1)
	{
		Logger::Log({ "Uniform \"", uniformName, "\" does not exist." }, LogType::Error);
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matrix);
}

ShaderProgram::~ShaderProgram()
{
	if (m_loadSuccessful)
	{
		DeallocateShaders();
	}
}
