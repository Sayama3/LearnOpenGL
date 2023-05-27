#version 330 core
layout(location = 0) out vec4 color;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform vec4 uniformColor;

void main()
{
//    color = vec4(0.75f, 0.75f, 0.0f, 1.0f);
    color = texture(ourTexture, texCoord) * vec4(vertexColor, 1) * uniformColor;
//    color = normalize(gl_Position);
}