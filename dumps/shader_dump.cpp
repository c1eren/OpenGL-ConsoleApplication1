#version 460 core

layout(location = 0) in vec3 position;
out vec4 vertex_Position;
uniform float offset;
uniform vec2 cursorXY;

void main() {
    //gl_Position = vec4(position.x - 0.5 + cursorXY.x, position.y + 0.5 + (cursorXY.y * -1), position.z, 1.0);
    //gl_Position = vec4(position.x * offset, position.y + offset, position.z, 1.0);
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);

    vertex_Position = gl_Position;
}

//gl_Position = vec4(aPos.x * offset, aPos.y + offset, aPos.z, 1.0);
//ourColor = aColor;

vec4 texColor = texture(texture1, TexCoords);
if (texColor.a < 0.2)
{
    discard;
}
FragColor = texColor;