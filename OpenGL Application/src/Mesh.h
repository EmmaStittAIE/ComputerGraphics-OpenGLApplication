#pragma once

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GraphicsDef.h"

class Mesh
{
private:
	GLuint m_vertexBufferID = 0;
	GLuint m_indexBufferID = 0;

	// Only use this if not using index buffer
	int m_vertexCount = 0;
	int m_pointCount = 0;

	void BindVertBuffer() const;
	static void UnbindVertBuffer();

	void BindIndexBuffer() const;
	static void UnbindIndexBuffer();

public:
	Mesh() = default;

	void ConstructCubePrimitive();
	void ConstructFromFile(std::string filePath);

	void Equip() const;
	void Unequip() const;

	// Getters
	int GetVertCount() const { return m_vertexCount; }
	int GetPointCount() const { return m_pointCount; }

	// Bools
	bool IsValid() const { return m_vertexBufferID != 0; }
	bool UsingIndexing() const{ return m_indexBufferID != 0; }

	~Mesh();
};