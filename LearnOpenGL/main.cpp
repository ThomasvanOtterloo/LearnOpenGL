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

int main()
{

	WindowManager window;
	if (!window.init(1200, 800, "LearnOpenGL"))
	{
		return -1;
	}
	Renderer renderer(window.getWindow());
	InputHandler inputHandler(window.getWindow());


	

	

	// 1. create vertices
	float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};

	float vertices2[] = {
		// second triangle
		0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
		0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right
		0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f// top 
	};
	// 2. Create and bind VBOs and add vertices
	VertexBuffers vertexBuffers(2); // 2 because we have 2 VBOs
	VAOManager vaoManager(2);       // 2 because we have 2 VAOs

	// First triangle setup
	vaoManager.BindVAO(0); // Bind the first VAO
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER, 0); // Bind the first VBO

	vertexBuffers.AddVertices(vertices, sizeof(vertices)); // Add vertices to the first VBO
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



	// Second triangle setup
	vaoManager.BindVAO(1); // Bind the second VAO
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER, 1); // Bind the second VBO

	// Add vertices to the second VBO
	vertexBuffers.AddVertices(vertices2, sizeof(vertices2)); 
	// position attribute
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// color attribute
	vaoManager.SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	




	// 5. Create and bind EBO (so VBO first, then VAO, then EBO) // EBO is optional here 
	// because we are using glDrawArrays

	/*ElementBuffer elementBuffer;
	elementBuffer.CreateElementBuffer();
	elementBuffer.BindElementBuffer();
	elementBuffer.AddIndices(indices, sizeof(indices));*/




	// X. Create and compile the vertex shader
	Shader shader;
	GLint vertexShader = shader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	GLint fragmentShader = shader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.shader");
	shader.CreateShaderProgram(vertexShader, fragmentShader);
	shader.UseShaderProgram();

	//create a second shader program
	Shader shader2;
	GLint vertexShader2 = shader2.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	GLint fragmentShader2 = shader2.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment2.shader");
	shader2.CreateShaderProgram(vertexShader2, fragmentShader2);
	shader2.UseShaderProgram();


	// Query the maximum number of vertex attributes supported by the GPU
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	// Main loop
	while (!window.shouldClose()) {
		inputHandler.processInput();

		renderer.render();


		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = shader.GetUniformLocation("ourUniColor");
		float offset = 0.05f;
		float positionLocation = shader.GetUniformLocation("offset");
		shader.UseShaderProgram();
		glUniform1f(positionLocation, offset); // move the second triangle more to the right
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		

		// Bind and draw the first VAO (VAO 0)
		vaoManager.BindVAO(0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shader2.UseShaderProgram();
		// Bind and draw the second VAO (VAO 1)
		vaoManager.BindVAO(1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shader2.GetUniformLocation("offset");
		glUniform1f(positionLocation, -offset); // move the first triangle more to the left


		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

