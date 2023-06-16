#version 330 core

#define NUMBER_OF_POINT_LIGHT 4
#define PI  3.14159265358979323846264338327950288419716939937510
#define Epsilon 0.00001

struct Material {
    vec3 ambient;
    sampler2D texture_diffuse0;
    sampler2D texture_specular0;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // The parameters of attenuation.
    float constant;
    float linear;
    float quadratic;

    // Parameters for spotlights
    float cutOff;
    float outerCutOff;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // The parameters of attenuation. Used if the light is not directional
    float constant;
    float linear;
    float quadratic;
};

vec3 CalcDirLight(Material material, DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Material material, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(Material material, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NUMBER_OF_POINT_LIGHT];
uniform SpotLight spotLight;

uniform vec3 viewPos = vec3(1);

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 color = CalcDirLight(material, directionalLight, normal, viewDir);

    for (int i = 0; i < NUMBER_OF_POINT_LIGHT; i++) {
       color += CalcPointLight(material, pointLights[i], normal, FragPos, viewDir);
    }

    color += CalcSpotLight(material, spotLight, normal, FragPos, viewDir);

    FragColor = vec4(color, 1.0);
}

vec3 CalcDirLight(Material material, DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, TexCoords));

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, TexCoords));

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, TexCoords));

    // result
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Material material, PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // attenuation
    vec3 lightDir = normalize(light.position - fragPos);
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, TexCoords));
    ambient *= attenuation;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, TexCoords));
    diffuse *= attenuation;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0, TexCoords));
    specular *= attenuation;

    // result
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(Material material, SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // SpotLight
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float spotLightIntensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);


    // ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.texture_diffuse0, TexCoords));;
    ambient *= attenuation;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, TexCoords));
    diffuse *= spotLightIntensity;
    diffuse *= attenuation;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.texture_specular0, TexCoords)));
    specular *= spotLightIntensity;
    specular *= attenuation;

    // result
    return (ambient + diffuse + specular);
}