#version 330 core

// Variables
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main(){
    // Adjust color based on texture values
    FragColor = texture(ourTexture, TexCoord);
}
