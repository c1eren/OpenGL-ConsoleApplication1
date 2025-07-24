#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexture;

// The columns of the matrix will have vertex attribute locations of 3, 4, 5, and 6.
layout (location = 3) in mat4 instanceMatrix;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexCoords = aTexture;
	gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0);
}
