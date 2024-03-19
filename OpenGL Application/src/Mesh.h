#pragma once

#include <vector>
#include "glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;

	glm::vec4 colour;

	glm::vec2 UV;
};

struct Mesh
{
	std::vector<Vertex> vertices;
};