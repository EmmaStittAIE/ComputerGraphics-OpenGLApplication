#pragma once

#include <vector>
#include "glm.hpp"

struct Vertex
{
	// TODO: Add texture coordinates (vec2) and normal (vec3)
	glm::vec3 position;

	glm::vec4 colour;
};

struct Mesh
{
	std::vector<Vertex> vertices;
};