#pragma once

#include <glad/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// If you're using GLFW time functions, you'll also need the GLFW header
// #include <GLFW/glfw3.h> 
// (Include it in your main or wherever you manage time if needed.)

#include <iostream>

// Defines several possible options for camera movement. 
// Merged your UP/DOWN directions with the LearnOpenGL directions.
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values (from LearnOpenGL)
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;

// A Camera class that processes input and calculates the 
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL.
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // processes input received from any keyboard-like input system
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event
    void ProcessMouseScroll(float yoffset);
    glm::vec3 GetPosition() { return Position; }



private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

