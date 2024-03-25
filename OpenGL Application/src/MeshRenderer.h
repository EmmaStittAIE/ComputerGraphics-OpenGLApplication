#pragma once

#include "TransformNode.h"

class ShaderProgram;
class Mesh;
class Texture;

class MeshRenderer : public TransformNode
{
public:
	// Managed by OpenGL - MeshRenderer does not own these
	Mesh* m_mesh;
	Texture* m_texture;

	void Draw(ShaderProgram* shader, const Mat4& vpMat) const;
};