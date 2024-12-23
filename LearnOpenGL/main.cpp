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
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	
	TextureManager textureManager(1);
	textureManager.BindTexture();
	textureManager.LoadTexture("C:/Users/Thomas/Downloads/container.jpg", GL_RGB);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	unsigned int texture1 = textureManager.getTextureId();




	TextureManager textureManager2(1);
	textureManager2.BindTexture();
	textureManager2.FlipTexture();
	textureManager2.LoadTexture("C:/Users/Thomas/Downloads/awesomeface.png", GL_RGBA);
	textureManager2.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	textureManager2.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	textureManager2.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	textureManager2.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	unsigned int texture2 = textureManager2.getTextureId();



	// 2. Create and bind VBOs and add vertices
	VertexBuffers vertexBuffers(1); 
	VAOManager vaoManager(1);       

	// First triangle setup
	vaoManager.BindVAO(); // Bind the first VAO
	
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER); // Bind the first VBO
	vertexBuffers.AddVertices(vertices, sizeof(vertices)); // Add vertices to the first VBO

	// Position attribute
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	// Color attribute
	//vaoManager.SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// // changed to 5 because we no longer have color
	// Texture coordinate attribute
	vaoManager.SetAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));



	// X. Create and compile the vertex shader
	Shader shader;
	GLint vertexShader = shader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	GLint fragmentShader = shader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.shader");
	shader.CreateShaderProgram(vertexShader, fragmentShader);
	shader.UseShaderProgram();

	// Set the texture uniform in the shader
	glUniform1i(glGetUniformLocation(shader.GetShaderProgram(), "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.GetShaderProgram(), "texture2"), 1);
	glUniform1i(glGetUniformLocation(shader.GetShaderProgram(), "zoomTexCoord"), 0);


	unsigned int transformLoc = glGetUniformLocation(shader.GetShaderProgram(), "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	
	
	
	float deltaTime = 0.0f;  // time between current frame and last frame
	float lastFrame = 0.0f;  // time of last frame
	// Main loop
	while (!window.shouldClose()) {
		inputHandler.processInput();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		inputHandler.processCameraInput(deltaTime);


		renderer.render();

		




		// bind textures on corresponding texture units
		textureManager.ActivateTexture(0);
		textureManager2.ActivateTexture(1);

		shader.UseShaderProgram();
		vaoManager.BindVAO();

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;			
			if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
				angle = glfwGetTime() * 25.0f;

			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);



			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//shader.setFloat("zoomTexCoord", inputHandler.getMixValue());
		shader.setFloat("zoomTexCoord", 1);

		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

	/*	glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 2.0f));
		shader.setMat4("model", model);*/

		
		float fov = camera.Zoom;
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), 600.0f / 600.0f, 0.1f, 50.0f);
		shader.setMat4("projection", projection);

		//glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

