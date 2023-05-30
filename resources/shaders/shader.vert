#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inColor;

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main()
{
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    vertexColor = inColor;
    texCoord = inTexCoord;
}