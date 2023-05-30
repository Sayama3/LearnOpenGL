#version 330 core
layout(location = 0) out vec4 color;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
void main()
{
    color = texture(ourTexture, texCoord);
}