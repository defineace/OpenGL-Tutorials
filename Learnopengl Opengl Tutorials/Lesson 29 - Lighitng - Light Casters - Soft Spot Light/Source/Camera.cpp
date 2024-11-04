#include "Camera.h"

Camera::Camera(  int screenWidth, int screenHeight, glm::vec3 position)
{
    // Screen Attributes
    SCREEN_HEIGHT = screenHeight;
    SCREEN_WIDTH = screenWidth;

    // Camera Attributes
    CAMERA_POSITION = position;
    
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt( CAMERA_POSITION, CAMERA_POSITION + CAMERA_FRONT, CAMERA_UP);
}

void Camera::processKeyboardInput( CAMERA_MOVEMENT direction, float deltaTime)
{

    const float speed = 2.0f * deltaTime;

    // Handles key inputs
	if (direction == FORWARD)
	{
		CAMERA_POSITION += speed * CAMERA_FRONT;
	}
	if (direction == BACKWARD)
	{
		CAMERA_POSITION -= speed * CAMERA_FRONT;
	}
	if (direction == LEFT)
	{
		CAMERA_POSITION -= speed * glm::normalize(glm::cross(CAMERA_FRONT, CAMERA_UP));
	}
	if (direction == RIGHT)
	{
		CAMERA_POSITION += speed * glm::normalize(glm::cross(CAMERA_FRONT, CAMERA_UP));
	}

    if (direction == UP)
    {
        CAMERA_POSITION.y += speed;
    }
    if (direction == DOWN)
    {
        CAMERA_POSITION.y -= speed;
    }
}

void Camera::processMouseInput( float xoffset, float yoffset)
{
    float sensitivity = 0.25f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    CAMERA_YAW += xoffset;
    CAMERA_PITCH += yoffset;

    if(CAMERA_PITCH > 89.0f)
    {
        CAMERA_PITCH = 89.0f;
    }
    if(CAMERA_PITCH < -89.0f)
    {
        CAMERA_PITCH = -89.0f;
    }

    glm::vec3 direction;

    // Using trignometry "Euler values" to create rotation
    direction.x = cos(glm::radians(CAMERA_YAW)) * cos(glm::radians(CAMERA_PITCH));
    direction.y = sin(glm::radians(CAMERA_PITCH));
    direction.z = sin(glm::radians(CAMERA_YAW)) * cos(glm::radians(CAMERA_PITCH));

    CAMERA_FRONT = glm::normalize(direction);
}

void Camera::processMouseScroll(float yoffset)
{
    CAMERA_FOV -= (float)yoffset;

    if(CAMERA_FOV < 1.0f)
    {
        CAMERA_FOV = 1.0f;
    }
    if(CAMERA_FOV > 45.0f)
    {
        CAMERA_FOV = 45.0f;
    }
}