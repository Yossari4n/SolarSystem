#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};

struct DirLight {
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
    
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 view_pos;
uniform Material material;
uniform DirLight dir_light;
#define NR_POINT_LIGHTS 4
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform Spotlight spotlight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotlight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 result;
    
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(view_pos - FragPos);
    
    result += CalcDirLight(dir_light, normal, viewDir);
    for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
        result += CalcPointLight(point_lights[i], normal, FragPos, viewDir);
    }
    result += CalcSpotlight(spotlight, normal, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    // ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse, TexCoords).rgb;
    
    // diffuse
    vec3 lightDir = -normalize(light.direction);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse, TexCoords).rgb;
    
    // specular
    vec3 lightReflect = reflect(-lightDir, normal);
    float spec = pow(max(dot(lightReflect, viewDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular, TexCoords).rgb;
    
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse, TexCoords).rgb;
    
    // diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse, TexCoords).rgb;
    
    // specular
    vec3 lightReflect = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, lightReflect), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular, TexCoords).rgb;
    
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotlight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // pure ambient
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, TexCoords));
    
    // diffuse
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse, TexCoords).rgb;
    
    // pure specular
    vec3 reflectDir = -reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular, TexCoords).rgb;
    
    // intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    
    // final color
    ambient = ambient * attenuation;
    diffuse = diffuse * attenuation * intensity;
    specular = specular * attenuation * intensity;
    
    return ambient + diffuse + specular;
}
