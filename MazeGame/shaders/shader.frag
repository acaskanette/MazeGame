#version 330 core

struct PointLight {
    vec3 position;
    
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 1

in vec3 fPosition;
in vec3 fNormal;
in vec2 fUV;

out vec4 color;

uniform vec3 cameraPosition;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;

// Function prototypes
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {    
    vec3 result = vec3(0.0f);
    vec3 viewDir = normalize(cameraPosition - fPosition);
    vec3 norm = normalize(fNormal);
    
    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, fPosition, viewDir);
        
    color = vec4(result, 1.0f);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (1.0f + light.linear * distance + light.quadratic * (distance * distance));    
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, fUV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, fUV));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, fUV));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}