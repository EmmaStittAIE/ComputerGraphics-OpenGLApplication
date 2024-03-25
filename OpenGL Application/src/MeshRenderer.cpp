#include "MeshRenderer.h"

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"

void MeshRenderer::Draw(ShaderProgram* shader, const Mat4& vpMat) const
{
	Mat4 mvpMat = vpMat * GetModelMatrix();
	shader->SetUniformMat4("mvpMat", &mvpMat[0][0]);
	
	m_mesh->EquipVertices();

	shader->SetUniformInt("textureSampler", 0);
	m_texture->BindBuffer(0);

	glDrawArrays(GL_TRIANGLES, 0, m_mesh->GetVertCount());

	m_texture->UnbindBuffer(0);

	m_mesh->UnequipVertices();
}
