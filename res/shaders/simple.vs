#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;

out vec2 FragPos;
out vec3 fCol;

uniform vec2 offsets[100];

void main()
{
	vec2 offset = offsets[gl_InstanceID];
	gl_Position = vec4(aPos + offset, 0.0, 1.0);
	fCol = aCol;
}
