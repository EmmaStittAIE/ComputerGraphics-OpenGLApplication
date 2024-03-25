#pragma once

#include "Maths.h"

class TransformNode
{
private:
	Vec3 m_position{ 0, 0, 0 };
	// TODO: consider changing these to something other than euler (if you do, update GetModelMatrix)
	Vec3 m_eulerRotation{ 0, 0, 0 };
	Vec3 m_scale{ 1, 1, 1 };

public:
	// Getters
	Mat4 GetModelMatrix() const;

	// Setters
	void SetPosition(Vec3 pos);
	void SetPosition(float x, float y, float z) { SetPosition({ x, y, z }); }

	void SetEulerRotation(Vec3 rotation);
	void SetEulerRotation(float x, float y, float z) { SetEulerRotation({ x, y, z }); }

	void SetScale(Vec3 scale);
	void SetScale(float x, float y, float z) { SetScale({ x, y, z }); }
};