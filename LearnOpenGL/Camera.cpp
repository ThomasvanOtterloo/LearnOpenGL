#include "Camera.h"




Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::SetCameraPosition(glm::vec3 position)
{
	cameraPos = glm::vec3(position);
}

void Camera::SetCameraDirection(glm::vec3 direction)
{
	cameraTarget = glm::vec3(direction);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);


}

void Camera::SetCameraAxis(glm::vec3 right, glm::vec3 up)
{
	up = glm::normalize(up);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}


