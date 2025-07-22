#version 460 core
out vec4 FragColor;

in VS_OUT
{
	vec2 TexCoords;
	vec4 PosCoords;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

void main()
{
	if (gl_FrontFacing)
	{
		FragColor = vec4(texture(texture_diffuse1, fs_in.TexCoords));
	}
	else
	{
		FragColor = vec4(texture(texture_diffuse2, fs_in.TexCoords));
	}


	//vec4 texCol = texture(texture_diffuse1, fs_in.TexCoords); 
	////FragColor = vec4(0.04, 0.28, 0.26, 1.0);
	//FragColor = texCol;
	//if (gl_FragCoord.x < 400)
	//{
	//	FragColor = vec4(texture(texture_diffuse1, fs_in.TexCoords));
	//}
	//else
	//{
	//	FragColor = 1 - fs_in.PosCoords;
	//}

}