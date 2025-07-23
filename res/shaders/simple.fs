#version 460 core

out vec4 FragColor;

in VS_OUT {
	vec2 texCoords;
} fs_in;

uniform	sampler2D texture_diffuse1;
uniform	sampler2D texture_diffuse2;
uniform	sampler2D texture_diffuse3;
uniform	sampler2D texture_specular1;
uniform	sampler2D texture_specular2;


void main()
{
	FragColor = vec4(texture(texture_diffuse1, fs_in.texCoords));
}
