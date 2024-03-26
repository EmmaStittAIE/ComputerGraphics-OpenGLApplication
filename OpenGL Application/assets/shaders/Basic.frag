#version 460

in vec3 interpolatedNormal;
in vec2 interpolatedUV;

uniform vec3 lightDirection;
uniform sampler2D diffuseSampler;
uniform sampler2D normalSampler;
uniform sampler2D specularSampler;

out vec4 pixelColour;

//FRAGMENT
void main()
{
	vec3 realNormal = normalize(interpolatedNormal);
	float lightIntensity = clamp(dot(-lightDirection, realNormal), 0, 1);

	vec3 diffuseColour = texture(diffuseSampler, interpolatedUV).rgb;
	vec3 normalColour = texture(normalSampler, interpolatedUV).rgb;
	vec3 specularColour = texture(specularSampler, interpolatedUV).rgb;

	pixelColour = vec4(diffuseColour * lightIntensity, 1);
	//pixelColour = vec4(lightIntensity, lightIntensity, lightIntensity, 1);
	//pixelColour = vec4(realNormal, 1);
}