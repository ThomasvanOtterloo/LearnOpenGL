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





int main()
{

	WindowManager window;
	if (!window.init(1200, 800, "LearnOpenGL"))
	{
		return -1;
	}
	Renderer renderer(window.getWindow());
	InputHandler inputHandler(window.getWindow());


	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	
	TextureManager textureManager(1);
	textureManager.BindTexture();
	textureManager.LoadTexture("C:/Users/Thomas/Downloads/container.jpg");
	textureManager.SetTextureWrappingAndFiltering();
	unsigned int texture = textureManager.getTextureId();



	// 2. Create and bind VBOs and add vertices
	VertexBuffers vertexBuffers(1); 
	VAOManager vaoManager(1);       

	// First triangle setup
	vaoManager.BindVAO(); // Bind the first VAO
	
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER); // Bind the first VBO
	vertexBuffers.AddVertices(vertices, sizeof(vertices)); // Add vertices to the first VBO

	// Position attribute
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	// Color attribute
	vaoManager.SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// Texture coordinate attribute
	vaoManager.SetAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));



	// Set the indices 
	unsigned int indices[] = {
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
	};

	
	ElementBuffer elementBuffer;
	elementBuffer.CreateElementBuffer();
	elementBuffer.BindElementBuffer();
	elementBuffer.AddIndices(indices, sizeof(indices));




	// X. Create and compile the vertex shader
	Shader shader;
	GLint vertexShader = shader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.shader");
	GLint fragmentShader = shader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.shader");
	shader.CreateShaderProgram(vertexShader, fragmentShader);
	shader.UseShaderProgram();



	// Main loop
	while (!window.shouldClose()) {
		inputHandler.processInput();

		renderer.render();

		shader.UseShaderProgram();

		// Bind and draw the first VAO (VAO 0)

		glBindTexture(GL_TEXTURE_2D, texture);
		vaoManager.BindVAO();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		


		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

