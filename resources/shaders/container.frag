#version 330 core

#define PI  3.14159265358979323846264338327950288419716939937510
#define Epsilon 0.00001

struct Material {
    vec3 ambient;
    sampler2D diffuseMat;
    sampler2D specularMat;
    float shininess;
};

struct Light {
    // Can be either a direction or a position
    vec4 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // The parameters of attenuation. Used if the light is not directional
    float constant;
    float linear;
    float quadratic;
};

bool IsDirectionalLight(Light light) {
    return abs(light.vector.w) < Epsilon;
}

uniform Material material;
uniform Light light;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos = vec3(1);

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(Normal);
    float attenuation = 1.0;
    vec3 lightDir;
    if(IsDirectionalLight(light)) {
        lightDir = normalize(-light.vector.xyz);
    } else {
        vec3 pos = light.vector.xyz;
        lightDir = normalize(pos - FragPos);
        float dist = length(pos - FragPos);
        attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
    }

    // ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuseMat, TexCoords));;
    ambient *= attenuation;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMat, TexCoords));
    diffuse *= attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specularMat, TexCoords)));
    specular *= attenuation;

    // result
    vec3 result = ambient + diffuse + specular;


    FragColor = vec4(result, 1.0);
}