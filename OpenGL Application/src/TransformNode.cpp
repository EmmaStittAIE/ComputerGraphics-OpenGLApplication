#include "TransformNode.h"

Mat4 TransformNode::GetModelMatrix() const
{
	Mat4 modelMatrix(1);

	modelMatrix = glm::translate(modelMatrix, m_position);
	
	// Rotate the model matrix by our euler rotation
	modelMatrix = glm::rotate(modelMatrix, m_eulerRotation.x, Vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, m_eulerRotation.y, Vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, m_eulerRotation.z, Vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, m_scale);

	return modelMatrix;
}

void TransformNode::SetPosition(Vec3 pos)
{
	m_position = pos;
}

void TransformNode::SetEulerRotation(Vec3 rotation)
{
	m_eulerRotation = rotation;
}

void TransformNode::SetScale(Vec3 scale)
{
	m_scale = scale;
}