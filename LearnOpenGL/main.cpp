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

	// configure global opengl state
    // -----------------------------
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS); // other possibilities: GL_LESS, GL_ALWAYS, GL_LEQUAL, GL_GEQUAL, GL_NOTEQUAL, GL_NEVER 

	// Print out Assimp version
	//std::cout << "Assimp version: " << aiGetVersionMajor() << "." << aiGetVersionMinor() << "." << aiGetVersionRevision() << std::endl;

	   // set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float cubeVertices[] = {
		// positions          // texture Coords
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
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	// cube vbo
	VertexBuffers cubeVBO(1);
	cubeVBO.BindVertexBuffers(GL_ARRAY_BUFFER);
	cubeVBO.AddVertices(cubeVertices, sizeof(cubeVertices));
	

	// cube VAO
	VAOManager cubeVAOManager(1);
	cubeVAOManager.BindVAO();
	cubeVAOManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	cubeVAOManager.SetAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


	// plane VBO
	VertexBuffers planeVBO(1);
	planeVBO.BindVertexBuffers(GL_ARRAY_BUFFER);
	planeVBO.AddVertices(planeVertices, sizeof(planeVertices));

	// plane VAO
	VAOManager planeVAOManager(1);
	planeVAOManager.BindVAO();
	planeVAOManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	planeVAOManager.SetAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));



	// load textures
	// -------------
	string cubeTexture = "C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/media/marble.jpg";
	string floorTexture = "C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/media/metal.png";

	TextureManager cubeTextureManager(1);
	cubeTextureManager.BindTexture();
	cubeTextureManager.LoadTexture(cubeTexture.c_str());
	cubeTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	cubeTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	cubeTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	cubeTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	TextureManager floorTextureManager(1);
	floorTextureManager.BindTexture();
	floorTextureManager.LoadTexture(floorTexture.c_str());
	floorTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	floorTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	floorTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	floorTextureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	
	
	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);


	// X. Create and compile the vertex shader
	Shader shader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/depth_testing.vert",
		"C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/depth_testing.frag");
	shader.use();
	

	
	
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
		shader.setInt("texture1", 0);

		// projection matrix/ view transformation
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1200.0f / 800.0f, 0.1f, 50.0f);
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		 

		// cube
		cubeVAOManager.BindVAO();
		cubeTextureManager.ActivateTexture(0);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	

		// plane
		shader.setInt("texture1", 1);
		planeVAOManager.BindVAO();
		floorTextureManager.ActivateTexture(1);
		
		model = glm::mat4(1.0f);
		shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);





 

		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

