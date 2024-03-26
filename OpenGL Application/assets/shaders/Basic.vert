#version 460

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 vertexUV;

layout (location = 2) in vec3 vertexNormal;

layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitangent;

uniform mat4 modelMat;
uniform mat4 mvpMat;

out vec3 interpolatedNormal;
out vec2 interpolatedUV;

//VERTEX
void main()
{
	interpolatedNormal = (modelMat * vec4(vertexNormal, 0.0)).xyz;
	interpolatedUV = vertexUV;

	gl_Position = mvpMat * vec4(vertexPos, 1.0);
}