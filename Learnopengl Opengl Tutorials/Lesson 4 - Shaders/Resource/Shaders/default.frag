#version 330 core

// Output FragColor
out vec4 FragColor;

// Input ourColor from vertex shader
in vec3 ourColor;

void main(){
    FragColor = vec4(ourColor, 1.0);
}
