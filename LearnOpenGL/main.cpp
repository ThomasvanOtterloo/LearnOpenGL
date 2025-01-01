#include <glad/glad.h>  
#include <GLFW/glfw3.h>
#include <iostream>
#include "WindowManager.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "VertexBuffers.h"
#include "Shader.h"
#include "VAOManager.h"
#include "ElementBuffer.h"
#include "TextureManager.h"
#include "Camera.h"
#include <string>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// assimp
#include <assimp/config.h>
#include <assimp/revision.h>
#include <assimp/version.h>

#include "Model.h"
#include <iostream>



int main()
{

	WindowManager window;
	if (!window.init(1200, 800, "LearnOpenGL"))
	{
		return -1;
	}
	Renderer renderer(window.getWindow());
	Camera camera;
	InputHandler inputHandler(window.getWindow(), camera);
	

	// Print out Assimp version
	std::cout << "Assimp version: " << aiGetVersionMajor() << "." << aiGetVersionMinor() << "." << aiGetVersionRevision() << std::endl;


	
	
	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// X. Create and compile the vertex shader
	Shader shader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/model_loading.vs",
		"C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/model_loading.fs");
	shader.use();
	

	// Load models
	Model model("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/media/backpack.obj");

	
	
	float deltaTime = 0.0f;  // time between current frame and last frame
	float lastFrame = 0.0f;  // time of last frame
	// Main loop
	while (!window.shouldClose()) {
		inputHandler.processInput();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		inputHandler.processCameraInput(deltaTime);

		// start rendering
		renderer.render();

		shader.use();

		// projection matrix/ view transformation
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1200.0f / 800.0f, 0.1f, 50.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
 


		// render the loaded model
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		// rotate it around the y-axis
		//modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));


	
		shader.setMat4("model", modelMatrix);
		model.Draw(shader);


		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

