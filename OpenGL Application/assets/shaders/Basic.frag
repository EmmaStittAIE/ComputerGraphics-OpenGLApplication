#version 460

in vec3 interpolatedColour;

out vec4 pixelColour;

void main()
{
	pixelColour = vec4(interpolatedColour, 1.0);
}