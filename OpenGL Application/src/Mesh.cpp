#include "Mesh.h"

#include <vector>

#include "Maths.h"
#include "Vertex.h"
#include "Logger.h"

void Mesh::BindVertBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
}

void Mesh::UnbindVertBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::BindIndexBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
}

void Mesh::UnbindIndexBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ConstructCubePrimitive()
{
	/*std::vector<Vertex> verts =
	{		// Position					 Normal						Colour						  UV
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(0.0f,  0.0f) },		// Front
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec2(1.0f,  0.0f) },
																   
			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(0.0f,  0.0f) },		// Back
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec2(1.0f,  0.0f) },
																   
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f) },		// Right
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(1.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec2(1.0f,  0.0f) },
																   
			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f) },		// Left
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(1.0f,  0.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec2(1.0f,  0.0f) },
																   
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(0.0f,  0.0f) },		// Top
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec2(1.0f,  0.0f) },
																   
			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(0.0f,  0.0f) },		// Bottom
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(1.0f,  0.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(1.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec2(1.0f,  0.0f) }
	};
	
	m_vertexCount = verts.size();

	glGenBuffers(1, &m_vertexBufferID);

	BindVertBuffer();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, verts.data(), GL_STATIC_DRAW);
	UnbindVertBuffer();*/
}

void Mesh::ConstructFromFile(std::string filePath)
{
	Assimp::Importer importer;
	const aiScene* fileScene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

	std::vector<Vertex> vertData;
	std::vector<unsigned short> indexData;

	if (fileScene->mNumMeshes <= 0)
	{
		Logger::Log({ "No meshes were loaded from file \"", filePath, "\"."}, LogType::Error);
		return;
	}

	aiMesh* mesh = fileScene->mMeshes[0];
	m_vertexCount = mesh->mNumVertices;

	vertData.reserve(mesh->mNumVertices);
	indexData.reserve(mesh->mNumFaces * 3);

	for (unsigned int i = 0; i < m_vertexCount; i++)
	{
		Vertex currentVert;

		currentVert.position.x = mesh->mVertices[i].x;
		currentVert.position.y = mesh->mVertices[i].y;
		currentVert.position.z = mesh->mVertices[i].z;

		currentVert.UV.x = mesh->mTextureCoords[0][i].x;
		currentVert.UV.y = mesh->mTextureCoords[0][i].y;

		currentVert.normal.x = mesh->mNormals[i].x;
		currentVert.normal.y = mesh->mNormals[i].y;
		currentVert.normal.z = mesh->mNormals[i].z;

		currentVert.tangent.x = mesh->mTangents[i].x;
		currentVert.tangent.y = mesh->mTangents[i].y;
		currentVert.tangent.z = mesh->mTangents[i].z;

		currentVert.bitangent.x = mesh->mBitangents[i].x;
		currentVert.bitangent.y = mesh->mBitangents[i].y;
		currentVert.bitangent.z = mesh->mBitangents[i].z;

		vertData.push_back(currentVert);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		indexData.push_back((unsigned short)mesh->mFaces[i].mIndices[0]);
		indexData.push_back((unsigned short)mesh->mFaces[i].mIndices[1]);
		indexData.push_back((unsigned short)mesh->mFaces[i].mIndices[2]);
	}

	m_pointCount = indexData.size();

	glGenBuffers(1, &m_vertexBufferID);

	BindVertBuffer();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, vertData.data(), GL_STATIC_DRAW);
	UnbindVertBuffer();

	glGenBuffers(1, &m_indexBufferID);

	BindIndexBuffer();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_pointCount, indexData.data(), GL_STATIC_DRAW);
	UnbindIndexBuffer();
}

void Mesh::Equip() const
{
	BindVertBuffer();
	Vertex::EnableAttributeArrays();
	UnbindVertBuffer();

	BindIndexBuffer();
}

void Mesh::Unequip() const
{
	Vertex::DisableAttributeArrays();

	UnbindIndexBuffer();
}

Mesh::~Mesh()
{
	if (IsValid())
	{
		glDeleteBuffers(1, &m_vertexBufferID);
	}

	if (UsingIndexing())
	{
		glDeleteBuffers(1, &m_indexBufferID);
	}
}
