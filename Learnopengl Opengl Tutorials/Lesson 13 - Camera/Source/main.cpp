#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>
#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

#include "Shader.h"

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(int argc,char* argv[]){

    // ###################################################################################################
    // MAIN_FUNCTION::Data
    // ###################################################################################################

    float vertices[] = {
        // Positions           // TexCoords
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // ###################################################################################################
    // MAIN_FUNCTION::OpenGL Configuration
    // ###################################################################################################

    // Init OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create opengl context window
    GLFWwindow* window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    // Z Buffer
    glEnable(GL_DEPTH_TEST);

    // ###################################################################################################
    // MAIN_FUNCTION::Shaders
    // ###################################################################################################

    // Checks how input variable can be used on current hardware
    int nrAttributes;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maxinum nr of vertex attributes supported: " << nrAttributes << std::endl;

    Shader shader("../Resource/Shaders/default.vert","../Resource/Shaders/default.frag");

    // ###################################################################################################
    // MAIN_FUNCTION::Buffers
    // ###################################################################################################

    // VAO VBO EBO
    unsigned int VAO, VBO;

    // Bind Buffers
    glGenVertexArrays(1 ,&VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Basically the VAO holds all this shit 

    // VBO BUFFER Copy vertices into buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define how to read the buffer array, basically where to find the position data
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Define how to read the buffer array, basicaly where to find the texcord data
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ###################################################################################################
    // MAIN_FUNCTION::TEXTURES
    // ###################################################################################################

    // ########## LOAD TEXTURE 1

    unsigned int texture_1;
    glGenTextures( 1, &texture_1);
    glBindTexture(GL_TEXTURE_2D, texture_1);

    // Config curretn textures options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ########## LOAD TEXTURE IMAGE 1
    int width, height, nrChannels;
    // Flip the texture image when loaded
    stbi_set_flip_vertically_on_load(true);
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

    // ########## LOAD TEXTURE 2

    unsigned int texture_2;
    glGenTextures( 1, &texture_2);
    glBindTexture(GL_TEXTURE_2D, texture_2);

    // Config curretn textures options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../Resource/Textures/texture_brick.png", &width, &height, &nrChannels, 0);

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
    
    // ###################################################################################################
    // MAIN_FUNCTION::Pre Render Shit
    // ###################################################################################################

    // Tell opengl for each sampler to which texture unit it blongs to (Only has to be done once)
    // Activate Shader, before setting shader uniforms

    shader.activate();

    shader.setInt("texture_2", 0);
    shader.setInt("texture_2", 1);



    // ###################################################################################################
    // MAIN_FUNCTION::Main Loop
    // ###################################################################################################

    while(!glfwWindowShouldClose(window)){

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Process User Input
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        // Process keyboard input
        processInput(window);

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Clear color and depth buffers
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Bind Textures
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_2);

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Activate shader program and bind to VAO
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        shader.activate();
        
        // Bind the VAO
        glBindVertexArray(VAO);

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Transformations
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        /*
        !!!!!!!!!!!! HOW OPENGL CAMERA WORKS !!!!!!!!!!!!!!

        This is how the glm::lookat() shit works
        
                         |
                         |
                         |
                        \ /
                         V


        More info on camera process
        Gram-Schmidt process, linear algebra
 
        # Camera Orientatino for zAxis, This is camera position and where its looking at
        Camera direction is formed by 
        glm::vec3 camera_position = glm::vec3( world_x , world_y , world_z )
        glm::vec3 camera_target = glm::vec3( world_x , world_y , world_z )
        glm::vev3 camera_direction = glm::normalize( camera_position - camera-target)

        # Camera orientation for xAxis, basically which is the right and up side of the camera
        Camera right is formed by
        glm::vec3 world_up =  glm::vec3( world_x , world_y , world_z)
        glm::vec3 camera_right = glm::normalize( glm::cross( world_up , camera_direction))

        # Camera orientation for yAxis
        Camera up is formed by
        glm::vec3 camera_up = glm::cross( camera_direction , camera_right )

    */




        // Camera is rotating around center
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        const float radius = 10.0f;
        float camera_xAxis = sin(glfwGetTime()) * radius;
        float camera_yAxis = cos(glfwGetTime()) * radius;
        float camera_zAxis = sin(glfwGetTime()) * radius;

        // ### VIEW ###
        // This is the virtal camera position,rotation in the opengl world
        // view = lookat( world xAxis location <x,y,z>, world yAxis location <x,y,z>, world zAxis location <x,y,z> )
        // view = lookat( camera position , camera front, camera up )
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt( glm::vec3(camera_xAxis, camera_zAxis, camera_yAxis)  , glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        // ### PROJECTION ###
        // This defines the camera type either orthographic or perspective
        // projection = perspective( angles to edges to near and far planes, widht of planes, and height of planes)
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);

        // Set uniforms for shaders
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Draw multiple cubes
        for ( unsigned int i=0; i<10; i++){
            float angle = 20.0f * i;

            // ### MODEL ### Normalize model vertices
            glm::mat4 model = glm::mat4( 1.0f );
            model = glm::translate( model,  cubePositions[i]);
            model = glm::rotate( model, glm::radians( angle ), glm::vec3( 1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        // MAIN_RENDER_LOOP::Check call events and Swap front and back buffers
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ###################################################################################################
    // MAIN_FUNCTION::Delete Buffers
    // ###################################################################################################

    glDeleteVertexArrays( 1, &VAO);
    glDeleteBuffers( 1, &VBO);

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