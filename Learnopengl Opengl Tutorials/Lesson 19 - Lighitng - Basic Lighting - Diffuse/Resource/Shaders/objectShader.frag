#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

// Variables
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{   
    float strength = 0.1f;
    vec3 ambient = strength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max( dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor =  vec4( result, 1.0f);
}