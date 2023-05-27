#version 330 core
layout(location = 0) out vec4 color;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
void main()
{
//    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//    color = vec4(texCoord,0,1);
    color = texture(ourTexture, texCoord);
//    color = vec4(vertexColor, 1);
}