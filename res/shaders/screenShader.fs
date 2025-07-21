#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture1;
//uniform vec2 texelSize;

void main()
{    
	vec2 texelSize = vec2(1.0 / 300.0);
	vec2 offsets[9] = vec2[] (
		vec2(-texelSize.x, texelSize.y),	// Top-left
		vec2( 0.0f		 , texelSize.y),	// Top-center
		vec2( texelSize.x, texelSize.y),	// Top-right
		vec2(-texelSize.x, 0.0f),			// Center-left
		vec2( 0.0f		 , 0.0f),			// Center-center
		vec2( texelSize.x, 0.0f),			// Center-right
		vec2(-texelSize.x, -texelSize.y),	// Bottom-left
		vec2( 0.0f		 , -texelSize.y),	// Bottom-center
		vec2( texelSize.x, -texelSize.y)	// Bottom-right
	);

	// SHARPEN KERNEL
	//float kernel[9] = float[] (
	//	-1, -1, -1,
	//	-1,  9, -1,
	//	-1, -1, -1
	//	);

	// BLUR KERNEL
	float kernel[9] = float[] (
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16
	);

	vec3 sampleTex[9];
	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture1, TexCoords.st + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for (int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
	}

	//FragColor = vec4(col, 1.0);

	//FragColor = vec4(vec3(1.0 - texture(screenTexture1, TexCoords)), 1.0); //Inverted colors
	//FragColor = vec4(TexCoords, 0.0, 1.0);
	FragColor = texture(screenTexture1, TexCoords);
	//float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
	//float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
	//FragColor = vec4(average, average, average, 1.0);
}