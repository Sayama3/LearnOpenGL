#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 transform = mat4(1.0);

void main()
{
    gl_Position = transform * vec4(inPosition, 1.0);
//    vertexColor = vec4(0.5,0.0,0.0,1.0);
//    vertexColor = (gl_Position + 1) * 0.5;
    vertexColor = inColor;
    texCoord = inTexCoord;
}