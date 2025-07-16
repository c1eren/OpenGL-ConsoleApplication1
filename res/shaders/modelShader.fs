#version 460 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;

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
uniform sampler2D texture_specular1;
uniform float shininess;

struct pointLightProperties {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};
uniform pointLightProperties plProperties;

struct PointLight {
    vec3 position;
};
#define NR_POINT_LIGHTS 3
uniform PointLight pointLights[NR_POINT_LIGHTS]; // An array of pointLight structs

// FUNCTIONS
vec3 calcPointLights(vec3 materialDiff, vec3 materialSpec, vec3 materialNorm, float shininess, vec3 lightPos, vec3 fragPos, pointLightProperties pl, vec3 viewDir);

void main()
{    
	// Properties
	vec3 norm	 = normalize(Normal); 
	vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);

    vec3 matDiff = vec3(texture(texture_diffuse1, TexCoords));
    vec3 matSpec = vec3(texture(texture_specular1, TexCoords));

    // Calculate point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += calcPointLights(matDiff, matSpec, norm, shininess, pointLights[i].position, FragPos, plProperties, viewDir);
	}

	// Output
    FragColor = vec4(result, 1.0);
}

vec3 calcPointLights(vec3 materialDiff, vec3 materialSpec, vec3 materialNorm, float shininess, vec3 lightPos, vec3 fragPos, pointLightProperties pl, vec3 viewDir)
{
    
    // Light direction vector 
	vec3 lightDir = normalize(lightPos - fragPos);

	// Diffuse shading 
	float diff = max(dot(materialNorm, lightDir), 0.0);

	// Specular shading
	vec3 reflectDir = reflect(-lightDir, materialNorm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	// Attenuation
	float distance = length(lightPos - fragPos);
	float attenuation = 1.0 / (pl.constant + pl.linear * distance + pl.quadratic * (distance * distance));

	// Results
	vec3 ambient =  pl.ambient * materialDiff;
	vec3 diffuse =  pl.diffuse * diff * materialDiff;
	vec3 specular = pl.specular * spec * materialSpec;

	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}


