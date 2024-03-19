#version 460

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec4 vertexColour;
layout (location = 3) in vec2 vertexUV;

uniform mat4 mvpMat;

out vec3 interpolatedNormal;
out vec4 interpolatedColour;
out vec2 interpolatedUV;

void main()
{
	interpolatedNormal = (mvpMat * vec4(vertexNormal, 0.0)).xyz;
	interpolatedColour = vertexColour;
	interpolatedUV = vertexUV;

	gl_Position = mvpMat * vec4(vertexPos, 1.0);
}