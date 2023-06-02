#version 330 core

struct Material {
    vec3 ambient;
    sampler2D diffuseMat;
    sampler2D specularMat;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos = vec3(1);

out vec4 FragColor;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuseMat, TexCoords));;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMat, TexCoords));
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specularMat, TexCoords)));
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}