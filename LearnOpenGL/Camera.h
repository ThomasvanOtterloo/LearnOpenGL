#pragma once
#include <GLM/fwd.hpp>
#include <GLM/vec3.hpp>
#include <GLM/geometric.hpp>
#include <GLM/ext/quaternion_geometric.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/gtx/string_cast.hpp>

enum MovementDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 view;

	float cameraSpeed = 2.5f;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame


public:
	Camera();
	~Camera();
	void SetCameraPosition(glm::vec3 position);
	void SetCameraDirection(glm::vec3 direction);
	void SetCameraAxis(glm::vec3 front, glm::vec3 right, glm::vec3 up);
	void SetCameraSpeed();
	glm::mat4 lookAt();
	
	void ProcessUserInput(enum MovementDirection);
	
	

};
