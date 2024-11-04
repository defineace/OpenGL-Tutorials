#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc,char* argv[]){
    
    std::cout << "Starting OpenGL" << std::endl;

    // ####################################### INITIALIZED OPENGL #################################################

    // Initialize GLFW
    glfwInit();

    // Set GLFW Version
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);

    // Initialize Window
    if( window == NULL ){
        std::cout << "Failed to Create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set Viewport
    glViewport( 0, 0, 800, 600);
    // Set Frame Callback Function
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback);

    // ####################################### SHADERS #################################################

    Shader shader( "../Resource/Shaders/default.vert", "../Resource/Shaders/default.frag" );
    Shader shader2( "../Resource/Shaders/default.vert", "../Resource/Shaders/fragment_shader_v0.frag" );

    // ####################################### VERTEX DATA #################################################

    // Square Vertex Array
    float vertices[] = {
        // Positions        // Colors (R*G*B)
        -0.25f, -0.5f, 0.0f,   0.5, 1.0, 0.0, // Top Right
         0.15f,  0.0f, 0.0f,   1.0, 0.5, 0.0, // Top Left
         0.0f,   0.5f, 0.0f,  0.0, 0.0, 0.5, // Bottom Left
         0.5f,  -0.4f, 0.0f,  0.5, 0.5, 0.5 // Bottom Right
    };

    // Square Vertex Incices
    unsigned int indices[] = {
        0, 1, 2, // First Triangle
        3, 1, 2 // Seccond Triangle
    };

    // ####################################### BUFFERS #################################################

    // VAO, VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO;
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set attributes pointer

    // Position Attibutes
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attibutes
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);

    // set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ####################### Pre Render Transformation

    // Transformation Rototate
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::scale(trans2, glm::vec3(1.5f));
    trans2 = glm::rotate(trans2, glm::radians(45.0f), glm::vec3(0.0f, 0.0, 1.0f));

    // ####################### Pre Render

    shader.activate();
    shader.setMat4("transform", trans);

    shader2.activate();
    shader2.setMat4("transform", trans2);

    // ####################### End of Pre Render


    // ####################################### MAIN LOOP #################################################    


    while(!glfwWindowShouldClose(window)){
        
        // User Input
        processInput(window);

        // Change Background Color
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

        // Clear Buffer
        glClear( GL_COLOR_BUFFER_BIT);

        // ####################### Transformation

        // Tranformation Rotation
        trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 1000.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.activate();
        shader.setMat4("transform", trans);

        trans2 = glm::rotate(trans2, glm::radians((float)glfwGetTime() / -1000.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        shader2.activate();
        shader2.setMat4("transform", trans2);

        // ####################### Render

        // Bind Vertex Array Object
        glBindVertexArray(VAO);

        // First Triangle
        shader.activate();
        glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
        
        // Seccond Triangle
        shader2.activate();
        glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)) );


        // ####################### End of Render

        // Bind Vertex Array
        glBindVertexArray(0);

        // SwapBuffers and Check Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

} // ########### END OF MAIN FUNCTION

// ####################################### FUNCTIONS #################################################

// Frame Buffer Callback Function
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport( 0, 0, width, height);
}

// Process Keyboard Input
void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS ){
        glfwSetWindowShouldClose(window, true);
    }
}