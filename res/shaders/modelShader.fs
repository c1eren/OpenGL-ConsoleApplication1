#version 460 core

in vec2 TexCoords;

out vec4 FragColor;

//struct Material{
//	sampler2D texture_diffuse1;
//	sampler2D texture_diffuse2;
//	sampler2D texture_diffuse3;
//	sampler2D texture_specular1;
//	sampler2D texture_specular2;
//	float shininess;
//};
//uniform Material material;

uniform sampler2D texture_diffuse1;

struct plProperties {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};
uniform plProperties plProp;

struct PointLight {
    vec3 position;
};
#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS]; // An array of pointLight structs

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}
