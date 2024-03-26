#include "MeshRenderer.h"

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"

void MeshRenderer::Draw(ShaderProgram* shader, const Mat4& vpMat) const
{
	Mat4 modelMat = GetModelMatrix();
	shader->SetUniformMat4("modelMat", &modelMat[0][0]);

	Mat4 mvpMat = vpMat * modelMat;
	shader->SetUniformMat4("mvpMat", &mvpMat[0][0]);
	
	shader->SetUniformInt("diffuseSampler", 1);
	shader->SetUniformInt("normalSampler", 2);
	shader->SetUniformInt("specularSampler", 3);
	m_diffuse->BindBuffer(1);
	m_normal->BindBuffer(2);
	m_specular->BindBuffer(3);

	m_mesh->Equip();

	if (m_mesh->UsingIndexing())
	{
		glDrawElements(GL_TRIANGLES, m_mesh->GetPointCount(), GL_UNSIGNED_SHORT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_mesh->GetVertCount());
	}

	m_mesh->Unequip();

	m_diffuse->UnbindBuffer(1);
	m_normal->UnbindBuffer(2);
	m_specular->UnbindBuffer(3);
}
