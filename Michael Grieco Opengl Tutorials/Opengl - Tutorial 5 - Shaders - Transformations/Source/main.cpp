#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string loadShaderSrc(const char* filename);

int main(int argc,char* argv[]){
    
    std::cout << "Starting OpenGL" << std::endl;

    int success;
    char infoLog[512];

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

    // ------------------------------------------------------------------
    // Compile Vertex Shader

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSrc = loadShaderSrc("../Resource/Shaders/default.vert");
    const GLchar* vertShader = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    // Vertex Shader Catch Error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if( !success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex shader comp.: " << std::endl << infoLog << std::endl;
    }
    
    // ------------------------------------------------------------------
    // Compile Fragment Shader

    unsigned int fragmentShaders[2];

    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShaderSrc = loadShaderSrc("../Resource/Shaders/default.frag");
    const GLchar* fragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[0]);

    // Fragment Shader Catch Error
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
        std::cout << "Error with Fragment Shader comp.: " << std::endl << infoLog << std::endl;
    }

    // ------------------

    fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShaderSrc = loadShaderSrc("../Resource/Shaders/fragment_shader_v0.frag");
    fragShader = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
    glCompileShader(fragmentShaders[1]);

    // Fragment Shader Catch Error
    glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
        std::cout << "Error with Fragment Shader comp.: " << std::endl << infoLog << std::endl;
    }


    // ------------------------------------------------------------------
    // Fragment Shader Program 1

    unsigned int shaderPrograms[2];

    shaderPrograms[0] = glCreateProgram();

    // Attach Shaders
    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    // Shader Program Catch Errors
    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
        std::cout << "Error with Shader Program comp.: " << std::endl << infoLog << std::endl;
    }

    // --------------------------
    // Fragment Shader Program 2

    shaderPrograms[1] = glCreateProgram();

    // Attach Shaders
    glAttachShader(shaderPrograms[1], vertexShader);
    glAttachShader(shaderPrograms[1], fragmentShaders[1]);
    glLinkProgram(shaderPrograms[1]);

    // Shader Program Catch Errors
    glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
        std::cout << "Error with Shader Program comp.: " << std::endl << infoLog << std::endl;
    }

    // Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaders[0]);
    glDeleteShader(fragmentShaders[1]);

    // ####################################### VERTEX DATA #################################################

    // Square Vertex Array
    float vertices[] = {
        // Positions        // Colors (R*G*B)
        -0.25f, -0.5f, 0.0f,   0.5, 0.0, 0.0, // Top Right
         0.15f,  0.0f, 0.0f,   0.0, 0.5, 0.0, // Top Left
         0.0f,   0.5f, 0.0f,  0.0, 0.0, 0.5, // Bottom Left
         0.5f,  -0.4f, 0.0f,  0.5, 0.5, 0.5 // Bottom Right
    };

    // Square Vertex Incices
    unsigned int indices[] = {
        0, 1, 2, // First Triangle
        2, 3, 0 // Seccond Triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attibutes
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);

    // set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Transformation Rototate
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUseProgram(shaderPrograms[0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[1], "transform"), 1, GL_FALSE, glm::value_ptr(trans));


    // ####################################### MAIN LOOP #################################################    


    while(!glfwWindowShouldClose(window)){
        
        // User Input
        processInput(window);

        // Change Background Color
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

        // Clear Buffer
        glClear( GL_COLOR_BUFFER_BIT);

        // Tranformation Rotation
        trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));
        


        // Draw
        glBindVertexArray(VAO);

        // First Triangle
        glUseProgram(shaderPrograms[0]);
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
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

// Load Shader Src File
std::string loadShaderSrc(const char* filename){
    std::ifstream file(filename, std::ios::binary);

    if(file){
        std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return(contents);
    }
    throw(errno);

}