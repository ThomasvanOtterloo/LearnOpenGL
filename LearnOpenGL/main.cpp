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


	
	// 1. Create and bind VBO
	VertexBuffers vertexBuffers(1);
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER);

	// 2. Copy vertices to VBO

	float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};


	// print size of vert
	std::cout << "1Size: " << sizeof(vertices) << std::endl;// prints 36
	vertexBuffers.AddVertices(vertices, sizeof(vertices)); 





	// 3. Create Vertex Array Object VAO
	VAOManager vaoManager;
	vaoManager.CreateVAO();

	// 4. Set vertex attributes pointers to VBO and enable
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	// 5. Create and bind EBO (so VBO first, then VAO, then EBO) // EBO is optional here 
	// because we are using glDrawArrays

	/*ElementBuffer elementBuffer;
	elementBuffer.CreateElementBuffer();
	elementBuffer.BindElementBuffer();
	elementBuffer.AddIndices(indices, sizeof(indices));*/




	// X. Create and compile the vertex shader
	Shader shader;
	shader.CreateVertexShader(1);
	shader.CreateFragmentShader(1);
	shader.CreateShaderProgram();
	shader.UseShaderProgram();




	// Main loop
	while (!window.shouldClose()) {
		inputHandler.processInput();

		renderer.render();

		shader.UseShaderProgram();

		vaoManager.BindVAO(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		glDrawArrays(GL_TRIANGLES, 0, 6);




		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

