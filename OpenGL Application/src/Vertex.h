#pragma once

#include "Maths.h"

struct Vertex
{
	glm::vec3 position;

	glm::vec2 UV;

	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	static void EnableAttributeArrays();
	static void DisableAttributeArrays();
};