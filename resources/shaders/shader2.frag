#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 uniformColor;

void main()
{
//    color = vec4(0.75f, 0.75f, 0.0f, 1.0f);
    color = uniformColor;
//    color = normalize(gl_Position);
}