#include "Camera.h"

Mat4 Camera::GetViewMatrix()
{
	return glm::inverse(GetModelMatrix());
}
