#version 460

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColour;

uniform mat4 mvpMat;

out vec3 interpolatedColour;

void main()
{
	interpolatedColour = vertexColour;

	gl_Position = mvpMat * vec4(vertexPos, 1.0);
}