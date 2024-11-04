#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material
{
    float shininess;
    sampler2D diffuseTexture;
    sampler2D specularTexture;
};

struct Light {
    vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// Uniform Variables
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{   
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuseTexture, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuseTexture, TexCoord).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
    vec3 specular = light.specular * spec * texture( material.specularTexture, TexCoord ).rgb;

    float distance = length( light.position - FragPos);
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Result
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4( result, 1.0f);
}

