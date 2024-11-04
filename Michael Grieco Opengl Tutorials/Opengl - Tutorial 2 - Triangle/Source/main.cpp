#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string loadShaderSrc(const char* filename);

const char* vertexSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"void main(){\n"
"    gl_Position = vec4(aPos.x , aPos.y , aPos.z , 1.0);\n;"
"}\n\0";

const char* fragmentSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4( 1.0f, 0.2f, 0.6f, 1.0f)\n;"
"}\n\0";



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
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Vertex Shader Catch Error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if( !success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error with vertex shader comp.: " << std::endl << infoLog << std::endl;
    }
    
    // ------------------------------------------------------------------
    // Compile Fragment Shader

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Fragment Shader Catch Error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error with Fragment Shader comp.: " << std::endl << infoLog << std::endl;
    }

    // ------------------------------------------------------------------
    // Fragment Shader Program 

    unsigned int shaderProgram;

    shaderProgram = glCreateProgram();

    // Attach Shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Shader Program Catch Errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error with Shader Program comp.: " << std::endl << infoLog << std::endl;
    }

    // Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ####################################### VERTEX DATA #################################################



    // Triangle Vertex Array
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    // Square Vertex Incices
    unsigned int indices[] = {
        0, 1, 2, // First Triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // ####################################### MAIN LOOP #################################################    


    while(!glfwWindowShouldClose(window)){
        
        // User Input
        processInput(window);


        // Change Background Color
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

        // Clear Buffer
        glClear( GL_COLOR_BUFFER_BIT);

        // Draw
        glBindVertexArray(VAO);

        // First Triangle
        glUseProgram(shaderProgram);
        glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );


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