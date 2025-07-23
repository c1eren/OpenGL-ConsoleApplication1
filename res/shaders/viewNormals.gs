#version 460 core
//layout (triangles) in;
//layout (line_strip, max_vertices = 6) out;
//
//in VS_OUT {
//vec3 normal;
//} gs_in[];
//const float MAGNITUDE = 0.4;
//uniform mat4 projection;
//void GenerateLine(int index)
//{
//gl_Position = projection * gl_in[index].gl_Position;
//EmitVertex();
//gl_Position = projection * (gl_in[index].gl_Position +
//vec4(gs_in[index].normal, 0.0) * MAGNITUDE);
//EmitVertex();
//EndPrimitive();
//}
//void main()
//{
//GenerateLine(0); // first vertex normal
//GenerateLine(1); // second vertex normal
//GenerateLine(2); // third vertex normal
//}

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
	mat3 normal;
};

in VS_OUT {	
	vec3 normalVec;
} gs_in[];

const float MAGNITUDE = 0.4;

void generateLine(int index)
{
	gl_Position = projection * gl_in[index].gl_Position; // Line starts at the position vertex
	EmitVertex();
	gl_Position = projection * (gl_in[index].gl_Position + vec4(gs_in[index].normalVec, 0.0) * MAGNITUDE); // Line ends at normaldirvector times magnitude
	EmitVertex();

	EndPrimitive();
}

void main()
{
	generateLine(0);
	generateLine(1);
	generateLine(2);
}
