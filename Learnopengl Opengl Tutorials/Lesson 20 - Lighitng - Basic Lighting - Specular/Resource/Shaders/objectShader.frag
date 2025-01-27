#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

// Variables
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{   
    // Ambient
    float strength = 0.1f;
    vec3 ambient = strength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    
    float diff = max( dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.75;

    vec3 viewDir = normalize( viewPos - FragPos );
    vec3 reflectDir = reflect( -lightDir, norm );

    float spec = pow( max( dot( viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Result
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor =  vec4( result, 1.0f);
}
