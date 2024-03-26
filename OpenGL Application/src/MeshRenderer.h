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
	Texture* m_diffuse;
	Texture* m_normal;
	Texture* m_specular;

	void Draw(ShaderProgram* shader, const Mat4& vpMat) const;
};