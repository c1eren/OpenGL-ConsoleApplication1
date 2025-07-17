#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

uniform int here;

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth){
    float z = depth * 2.0 - 1.0; // Back to Normalized Device Coordinates
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{    
    //float depth = linearizeDepth(gl_FragCoord.z) / far; // Far for demo
    if (here == 1)
    {
        FragColor = vec4(0.04, 0.28, 0.26, 1.0);
    }
    else
    {
        FragColor = texture(texture1, TexCoords);
    }
    //FragColor = vec4(vec3(depth), 1.0);
}