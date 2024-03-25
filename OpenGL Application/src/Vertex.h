#pragma once

#include "Maths.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;

	glm::vec4 colour;

	glm::vec2 UV;

	static void EnableAttributeArrays();
	static void DisableAttributeArrays();
};