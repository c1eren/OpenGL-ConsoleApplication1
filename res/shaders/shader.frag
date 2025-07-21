#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D f_texture1;
uniform sampler2D f_texture2;
uniform sampler2D f_texture3;
uniform sampler2D f_texture4;
uniform float f_mix;
uniform int u_ObjectType; // 0 = cube, 1 = floor


void main()
{

	if (u_ObjectType == 0) 
	{
		//FragColor = mix(texture(f_texture1, TexCoord), texture(f_texture2, TexCoord), 0.2f) + vec4(ourColor, 1.0) * f_mix;
		FragColor = texture(f_texture1, TexCoord);
	}
	else if (u_ObjectType == 1)
	{
		FragColor = texture(f_texture4, TexCoord);
		//FragColor = vec4(1.0, 0.0, 0.0, 1.0); // red
		//FragColor = vec4(ourColor, 0.5f);
	}

	//FragColor = texture(f_texture1, TexCoord) * vec4(ourColor, 1.0)
	//vec2 TexCoord_smiley = vec2(TexCoord.s * -1, TexCoord.t);
	//vec2 TexCoord_smiley1 = vec2(TexCoord * 2);
	//FragColor = texture(f_texture1, TexCoord);
}
