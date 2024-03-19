#version 460

in vec3 interpolatedNormal;
in vec4 interpolatedColour;
in vec2 interpolatedUV;

uniform vec3 lightDirection;
uniform sampler2D textureSampler;

out vec4 pixelColour;

void main()
{
	//vec3 realNormal = normalize(interpolatedNormal);

	//float lightIntensity = clamp(dot(-lightDirection, realNormal), 0, 1);

	vec3 textureColour = texture(textureSampler, interpolatedUV).rgb;

	//pixelColour = vec4(lightIntensity, lightIntensity, lightIntensity, 1);

	pixelColour = vec4(textureColour, 1);
}