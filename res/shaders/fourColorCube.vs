#version 460 core
layout (location = 0) in vec3 aPos;

// Note that the order of the variables is important here
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat3 normals;
};

uniform mat4 model;

void main()
{  
    gl_Position = projection * view * model * vec4(aPos, 1.0);    
}