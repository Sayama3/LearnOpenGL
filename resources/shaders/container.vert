#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
    FragPos = vec3(model * vec4(inPosition, 1.0));
    // TODO: have the NormalMatrix in uniform as it's costly.
    Normal = mat3(transpose(inverse(model))) * inNormal;
    TexCoords = inTexCoord;
}