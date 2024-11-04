#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "Shader.h"

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc,char* argv[]){

    // #######################################################  OpenGL

    // Init OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create opengl context window
    GLFWwindow* window = glfwCreateWindow( 800, 600, "LearnOpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // Set Window Size
    glViewport( 0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // ####################################################### Shaders

    // Checks how input variable can be used on current hardware
    int nrAttributes;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maxinum nr of vertex attributes supported: " << nrAttributes << std::endl;


    Shader shader("../Resource/Shaders/default.vert","../Resource/Shaders/default.frag");

    // ####################################################### Data

    float vertices[] = {
        // Positions          // Color           // TexCords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // ####################################################### Buffers

    // VAO VBO EBO
    unsigned int VAO, VBO, EBO;

    // Bind Buffers
    glGenVertexArrays(1 ,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Basically the VAO holds all this shit 

    // VBO BUFFER Copy vertices into buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Define how to read the buffer array, basically where to find the position data
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Define how to read the buffer array, basicaly where to find the color data
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define how to read the buffer array, basicaly where to find the texcord data
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // EBO add indicces to VAO 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // ####################################################### Pre Render Shit

    // ########## LOAD TEXTURE

    unsigned int texture;
    glGenTextures( 1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture);

    // Config curretn textures options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Flip the texture image when loaded
    stbi_set_flip_vertically_on_load(true);

    // Load texture image
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../Resource/Textures/sprite_character_pose_standing.png", &width, &height, &nrChannels, 0);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::Failed_TO_LOAD\n" << std::endl;
    }

    stbi_image_free(data);

    // ####################################################### Main Loop

    while(!glfwWindowShouldClose(window)){
        
        // Process keyboard input
        processInput(window);
        
        // Add background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        shader.activate();
 
        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Draw vertices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Check call events and Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate Opengl
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0 , 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
