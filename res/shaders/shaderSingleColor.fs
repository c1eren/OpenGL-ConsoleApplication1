#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
struct Material{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	float shininess;
};
uniform Material material;

void main()
{    
	vec4 texCol = texture(material.texture_diffuse1, TexCoords); 
	//FragColor = vec4(0.04, 0.28, 0.26, 1.0);
	FragColor = texCol;
}