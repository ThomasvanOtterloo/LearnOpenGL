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

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>




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
	





	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};





	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  -1.0f,  0.0f),
	glm::vec3(1.0f,  1.0f, -3.0f),
	};




	// 2. Create and bind VBOs and add vertices
	VertexBuffers vertexBuffers(1); 
	VAOManager vaoManager(1);       

	// First triangle setup
	vaoManager.BindVAO(); // Bind the first VAO
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER); // Bind the first VBO
	vertexBuffers.AddVertices(vertices, sizeof(vertices)); // Add vertices to the first VBO
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
	vaoManager.SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	// create second vao for the second cube
	VAOManager vaoManager2(1);
	vaoManager2.BindVAO();
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER);
	vertexBuffers.AddVertices(vertices, sizeof(vertices));
	vaoManager2.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));





	// X. Create and compile the vertex shader
	Shader shader;
	Shader lightSourceShader;

	GLint vertexShader = shader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	GLint fragmentShader = shader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.shader");
	shader.CreateShaderProgram(vertexShader, fragmentShader);
	shader.UseShaderProgram();

	GLint lightVertexShader = lightSourceShader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/VertexLightSource.shader");
	GLint lightFragmentShader = lightSourceShader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/FragmentLightSource.shader");
	lightSourceShader.CreateShaderProgram(lightVertexShader, lightFragmentShader);
	lightSourceShader.UseShaderProgram();

	
	
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

		glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		//glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
		

		shader.UseShaderProgram();
		shader.setVec3("objectColor", objectColor);
		shader.setVec3("lightColor", lightColor);
		shader.setVec3("lightPos", cubePositions[1]);
		shader.setVec3("viewPos", camera.Position);

		// view/projection transformations
		
		// projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1200.0f / 800.0f, 0.1f, 50.0f);
		shader.setMat4("projection", projection);

		// view transformation
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		// transform the cube
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[0]);
		shader.setMat4("model", model);

		// render the cube
		vaoManager.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// render the second cube
		// copy the projection and view from the first cube so the second cube is in the same view
		lightSourceShader.UseShaderProgram();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);

		glm::mat4 lampModel = glm::mat4(1.0f);
		lampModel = glm::translate(lampModel, cubePositions[1]);
		lampModel = glm::rotate(lampModel, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));

		// translates the light source
		cubePositions[1].x = 1.0f + sin(glfwGetTime()) * 4.0f;
		cubePositions[1].y = sin(glfwGetTime() / 2.0f) * 4.0f;

		lampModel = glm::scale(lampModel, glm::vec3(0.15f));
		lightSourceShader.setMat4("model", lampModel);

		
		vaoManager2.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 36);


	
		

		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

