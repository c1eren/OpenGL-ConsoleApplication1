#version 460 core

in vec2 TexCoords;
out vec4 FragColor;


uniform	sampler2D texture_diffuse1;
uniform	sampler2D texture_diffuse2;
uniform	sampler2D texture_diffuse3;
uniform	sampler2D texture_specular1;
uniform	sampler2D texture_specular2;


void main()
{
	FragColor = vec4(texture(texture_diffuse2, TexCoords));
}
