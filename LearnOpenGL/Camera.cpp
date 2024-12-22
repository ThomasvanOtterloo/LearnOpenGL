#include "Camera.h"



Camera::Camera()
{
	// Default initialization
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);         // Starting camera position
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);      // Default forward direction
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);          // Default up direction

	cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp)); // Right vector
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);      // Target position (default origin)
}

Camera::~Camera()
{
}

void Camera::SetCameraPosition(glm::vec3 position)
{
	cameraPos = position;
}

void Camera::SetCameraDirection(glm::vec3 target)
{
	cameraTarget = target;
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraFront = -cameraDirection; // Update the front direction

}

void Camera::SetCameraAxis(glm::vec3 front, glm::vec3 right, glm::vec3 up)
{
	// Set the camera's orientation vectors dynamically
	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(cameraFront, up));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::SetCameraSpeed()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	cameraSpeed = 2.5f * deltaTime;
}

glm::mat4 Camera::lookAt() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// Debugging
	std::cout << "Camera Position: " << glm::to_string(cameraPos) << std::endl;
	std::cout << "Camera Target: " << glm::to_string(cameraPos + cameraFront) << std::endl;
	std::cout << "Camera Up: " << glm::to_string(cameraUp) << std::endl;
	std::cout << "View Matrix: " << glm::to_string(view) << std::endl;

	return view;
}


void Camera::ProcessUserInput(MovementDirection direction) {
	if (direction == FORWARD)
		cameraPos += cameraSpeed * cameraFront;
	if (direction == BACKWARD)
		cameraPos -= cameraSpeed * cameraFront;
	if (direction == LEFT)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (direction == RIGHT)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Recalculate cameraFront dynamically
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraFront = -cameraDirection;

	// Debugging
	std::cout << "Camera Position: (" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")" << std::endl;
	std::cout << "Camera Front: (" << cameraFront.x << ", " << cameraFront.y << ", " << cameraFront.z << ")" << std::endl;
}
