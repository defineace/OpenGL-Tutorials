#version 330 core

// Variables
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(){
    // Combined texture value with color uniform attribute
    FragColor =  texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}
