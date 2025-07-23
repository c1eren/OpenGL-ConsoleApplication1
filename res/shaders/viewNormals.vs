#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

//out VS_OUT {
//vec3 normal;
//} vs_out;
//uniform mat4 view;
//uniform mat4 model;
//void main()
//{
//gl_Position = view * model * vec4(aPos, 1.0);
//mat3 normalMatrix = mat3(transpose(inverse(view * model)));
//vs_out.normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));
//}

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
	mat3 normal;
};

uniform mat4 model;

out VS_OUT {
	vec3 normalVec;
} vs_out;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0);
	vs_out.normalVec = normalize(normal * aNormal); // Take our normal matrix and apply to the normals to convert to view-space
}
