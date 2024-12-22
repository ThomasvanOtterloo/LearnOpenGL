#pragma once
#include <GLM/fwd.hpp>
#include <GLM/vec3.hpp>
#include <GLM/geometric.hpp>
#include <GLM/ext/quaternion_geometric.hpp>
class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;


public:
	Camera();
	~Camera();
	void SetCameraPosition(glm::vec3 position);
	void SetCameraDirection(glm::vec3 direction);
	void SetCameraAxis(glm::vec3 right, glm::vec3 up);
	
	
	

};
