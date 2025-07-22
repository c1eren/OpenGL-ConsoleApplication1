#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 worldPosition;

struct Material{
	sampler2D texture_diffuse1;
	float shininess;
};
uniform Material material;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform int type; // 1 for reflect 0 for refract

void main()
{    
	if (type == 1)
	{
		vec3 I = normalize(worldPosition - cameraPos); // Direction vector
		vec3 R = reflect(I, normalize(Normal));	  // Use normal direction vectors to calculate reflection factor
		FragColor = vec4(texture(skybox, R).rgb, 1.0);
	}
	if (type == 0)
	{
		float ratio = 1.00 / 1.33;
		vec3 I = normalize(worldPosition - cameraPos);
		vec3 R = refract(I, normalize(Normal), ratio);
		FragColor = vec4(texture(skybox, R).rgb, 1.0);
	}
	

	//vec4 matTex = vec4(texture(material.texture_diffuse1, TexCoords));
	//vec4 skyTex = vec4(texture(skybox, R).rgb, 1.0);
	//FragColor = mix(texture(skybox, R), texture(material.texture_diffuse1, TexCoords), 0.4);

	//vec4 texCol = texture(material.texture_diffuse1, TexCoords); 
	//FragColor = vec4(0.04, 0.28, 0.26, 1.0);
	//FragColor = texCol;
	//FragColor = vec4(TexCoords, 0.5, 1.0);
}