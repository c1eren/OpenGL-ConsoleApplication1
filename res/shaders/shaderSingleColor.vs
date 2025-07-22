#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out VS_OUT 
{
    vec2 TexCoords;
    vec4 PosCoords;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{  
    vs_out.TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.PosCoords = model * vec4(aPos, 1.0);
    gl_PointSize = gl_Position.z;
    
}