#pragma once

#include "TransformNode.h"

class Camera : public TransformNode
{
public:
	// Getters
	Mat4 GetViewMatrix();
};