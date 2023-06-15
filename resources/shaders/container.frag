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
    //W need to be != 0 to be
    vec4 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // The parameters of attenuation. Used if the light is not directional
    float constant;
    float linear;
    float quadratic;

    // Parameters for spotlights
    float cutOff;
    float outerCutOff;
};

bool IsDirectionalLight(Light light) {
    return abs(light.position.w) < Epsilon && length(light.direction) > Epsilon;
}

bool IsPointLight(Light light) {
    return abs(light.position.w) > Epsilon;
}

bool IsSpotLight(Light light) {
    return abs(light.position.w) > Epsilon && length(light.direction) > Epsilon;
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
    float spotLightIntensity = 1.0;
    float theta = -1;
    bool isSpotLight = false;
    vec3 lightDir;
    if(IsDirectionalLight(light)) {
        lightDir = normalize(-light.direction);
    } else if (IsPointLight(light)) {
        vec3 lightPos = light.position.xyz;
        lightDir = normalize(lightPos - FragPos);
        float dist = length(lightPos - FragPos);
        attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
        isSpotLight = IsSpotLight(light);
        if(isSpotLight) {
            theta = dot(lightDir, normalize(-light.direction));
            float epsilon = light.cutOff - light.outerCutOff;
            spotLightIntensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        }
    }

    vec3 color;

    // ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(material.diffuseMat, TexCoords));;
    ambient *= attenuation;

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMat, TexCoords));
    diffuse *= spotLightIntensity;
    diffuse *= attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specularMat, TexCoords)));
    specular *= spotLightIntensity;
    specular *= attenuation;

    // result
    color = ambient + diffuse + specular;

    FragColor = vec4(color, 1.0);
}