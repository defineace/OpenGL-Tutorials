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


int main(int argc,char* argv[]){

    // #######################################################  OpenGL

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


    // ####################################################### TEXTURES

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
    



    // ####################################################### Pre Render Shit

    // ############## Activate shader

    // Tell opengl for each sampler to which texture unit it blongs to (Only has to be done once)
    // Activate Shader, before setting shader uniforms

    shader.activate();

    glUniform1i(glGetUniformLocation(shader.ID, "texture_1"), 0);
    shader.setInt("texture_2", 1);


    // ############## Camera Transformation

    /*
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    Local Space > World Space > View Space > Clip Space > Screen Space
    
    ### Add it all together to create a camera for 3D ### 
    V,clip = M,projection * M,view * M,model * V,local

    ### Orthographic ortho( screen_x0, screen_x1, screen_y0, screen_y1, screen_z0, screen_z1)
    glm::ortho( 0.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    */



  
    // ### MODEL ### Normalize model vertices
    glm::mat4 model = glm::mat4( 1.0f );
    // Transform model like rotate, scale, translate
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3( 1.0f, 0.0f, 0.0f));

    // ### VIEW ### This the virtal camera position in the opengl world
    glm::mat4 view = glm::mat4(1.0f);
    // Transform view like rotate, scale, translate
    view = glm::translate(view, glm::vec3( 0.0f, 0.0f, -3.0f));

    // ### PROJECTION ### This defines the camera type either orthographic or perspective
    // perspective( angles to edges to near and far planes, widht of planes, and height of planes)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);


    // Set uniform variables for shaders
    unsigned int modelLoc = glGetUniformLocation( shader.ID, "model");
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation( shader.ID, "view");
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, &view[0][0]);

    shader.setMat4("projection", projection);





    // ####################################################### Main Loop

    while(!glfwWindowShouldClose(window)){
        
        // Process keyboard input
        processInput(window);
        
        // Add background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ------------------------------------------------

        // Bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_2);


        // ------------------------------------------------
        
        // Use shader program
        shader.activate();

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
