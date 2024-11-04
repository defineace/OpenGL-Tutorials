#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAMERA_MOVEMENT
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    // Screen Attributs
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

    // Camera Attributes
    glm::vec3 CAMERA_POSITION = glm::vec3( 1.0f, 1.0f, 1.0f);
    glm::vec3 CAMERA_FRONT = glm::vec3( 0.0f, 0.0f, -1.0f);
    glm::vec3 CAMERA_UP = glm::vec3( 0.0f, 1.0f, 0.0f); 

    float CAMERA_YAW = -90.0f;
    float CAMERA_PITCH = 0.0f;

    // Camera Options
    float CAMERA_FOV = 45.0f;

    // Constructor
    Camera( int screenWidth, int screenHeight, glm::vec3 position);
    
    // Get View matrix
    glm::mat4 getViewMatrix();

    // Proccess keyboard input
    void processKeyboardInput( CAMERA_MOVEMENT direction, float deltaTime);
    void processMouseInput( float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
};

#endif