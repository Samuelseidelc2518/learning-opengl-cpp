#version 330 core
out vec4 FragColor;

// inputs the color from the Vertex Shader
in vec3 color;

in vec2 textCoord;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, textCoord);
}