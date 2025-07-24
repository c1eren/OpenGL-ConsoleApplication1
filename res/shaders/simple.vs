#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aOffset;

out vec2 FragPos;
out vec3 fCol;

void main()
{

	gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
	fCol = aCol;
}
