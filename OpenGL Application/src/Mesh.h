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
	// Implement vertex indexing
	//GLuint m_indexBufferID = 0;

	int m_vertexCount = 0;

	void BindBuffer() const;
	static void UnbindBuffer();

public:
	Mesh() = default;

	void ConstructCubePrimitive();
	void ConstructFromFile(std::string filePath);

	void EquipVertices() const;
	void UnequipVertices() const;

	// Getters
	int GetVertCount() const { return m_vertexCount; }
	bool IsValid() const { return m_vertexBufferID != 0; }

	~Mesh();
};