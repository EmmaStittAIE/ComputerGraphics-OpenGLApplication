#include "Mesh.h"

#include <vector>

#include "Maths.h"
#include "Vertex.h"

// temp
#include <iostream>

void Mesh::BindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void Mesh::UnbindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::ConstructCubePrimitive()
{
	std::vector<Vertex> verts =
	{		// Position					 Normal						Colour						  UV
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Front
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Back
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },

			{ Vec3(1.0f, -1.0f, -1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Right
			{ Vec3(1.0f,  1.0f, -1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f,  1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(1.0f,  1.0f,  1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(1.0f,  1.0f, -1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f,  1.0f), Vec3(1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Left
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },

			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Top
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f,  1.0f, -1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(1.0f,  1.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f,  1.0f, -1.0f), Vec3(0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2(1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  0.0f) },		// Bottom
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(1.0f, -1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(1.0f, -1.0f, -1.0f), Vec3(0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(1.0f,  0.0f) }
	};
	
	m_vertexCount = verts.size();

	glGenBuffers(1, &m_vertexBufferID);

	BindBuffer();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, verts.data(), GL_STATIC_DRAW);
	Vertex::EnableAttributeArrays();
	UnbindBuffer();
}

void Mesh::ConstructFromFile(std::string filePath)
{
	Assimp::Importer importer;
	const aiScene* fileScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	if (fileScene->mNumMeshes <= 0)
	{
		// TODO: error logging
		return;
	}

	aiMesh* mesh = fileScene->mMeshes[0];

	std::vector<Vertex> verts;
	std::vector<unsigned short> indices;

	m_vertexCount = mesh->mNumVertices;

	for (int i = 0; i < m_vertexCount; i++)
	{
		Vertex currentVert;

		currentVert.position.x = mesh->mVertices[i].x;
		currentVert.position.y = mesh->mVertices[i].y;
		currentVert.position.z = mesh->mVertices[i].z;

		currentVert.position.x = mesh->mNormals[i].x;
		currentVert.position.y = mesh->mNormals[i].y;
		currentVert.position.z = mesh->mNormals[i].z;

		currentVert.colour.x = mesh->mColors[0][i].r;
		currentVert.colour.y = mesh->mColors[0][i].g;
		currentVert.colour.z = mesh->mColors[0][i].b;
		currentVert.colour.w = mesh->mColors[0][i].a;

		currentVert.UV.x = mesh->mTextureCoords[0][i].x;
		currentVert.UV.y = mesh->mTextureCoords[0][i].y;

		verts.push_back(currentVert);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		indices.push_back((unsigned short)mesh->mFaces[i].mIndices[0]);
		indices.push_back((unsigned short)mesh->mFaces[i].mIndices[1]);
		indices.push_back((unsigned short)mesh->mFaces[i].mIndices[2]);
	}

	glGenBuffers(1, &m_vertexBufferID);

	BindBuffer();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, verts.data(), GL_STATIC_DRAW);
	UnbindBuffer();

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void Mesh::EquipVertices() const
{
	BindBuffer();
	Vertex::EnableAttributeArrays();
	UnbindBuffer();
}

void Mesh::UnequipVertices() const
{
	Vertex::DisableAttributeArrays();
}

Mesh::~Mesh()
{
	if (IsValid())
	{
		glDeleteBuffers(1, &m_vertexBufferID);
	}
}
