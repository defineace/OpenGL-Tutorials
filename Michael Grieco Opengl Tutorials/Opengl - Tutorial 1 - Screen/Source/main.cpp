#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc,char* argv[]){
    
    // Initialize GLFW
    glfwInit();

    // Set GLFW Version
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
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
    glViewport( 0, 0, 800, 800);
    // Set Frame Callback Function
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        
        // User Input
        processInput(window);

        // Change Background Color
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

        // Clear Buffer
        glClear( GL_COLOR_BUFFER_BIT);

        // SwapBuffers and Check Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport( 0, 0, width, height);
}

// Process Keyboard Input
void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS ){
        glfwSetWindowShouldClose(window, true);
    }
}