#version 330 core
layout(location = 0) out vec4 color;
in vec4 vertexColor;

void main()
{
//    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    color = vertexColor;
}