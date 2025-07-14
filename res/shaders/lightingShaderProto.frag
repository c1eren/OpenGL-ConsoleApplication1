#version 460 core

struct Material {
	sampler2D diffuse; // Texture becomes our diffuse color
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material material;

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 lightPos;

	float constant;
	float linear;
	float quadratic;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
};
uniform Light light;

uniform float time;
uniform vec3 viewPos;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	vec3 lightDir = normalize(light.lightPos - FragPos);

	// Flashlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Emission
	vec3 emission = texture(material.emission, TexCoord).rgb;
	
	// Attenuation
	float distance = length(light.lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	// Diffused
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0); // max() clamps at 0 to prevent breaking if light source is behind object
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos); // techincally works as viewPos - FragPos if using view matrix (since camera is (0,0,0))
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	

	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;
	vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

	ambient *= attenuation;
	diffuse *= (intensity * attenuation);
	specular *= (intensity * attenuation);
	emission *= (intensity * attenuation);

	
	// Phong
	vec3 result = ambient + diffuse + specular;
	if (intensity != 0)
	{
		FragColor = vec4(result + emission, 1.0);
	}
	else
	{
		FragColor = vec4(result, 1.0);
	}
	//vec3 result = ambient + diffuse;
	//FragColor = texture(material.diffuse, TexCoord) * vec4(result, 1.0);


}
