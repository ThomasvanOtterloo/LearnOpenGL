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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(1.0f,  1.0f, -3.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};




	// 2. Create and bind VBOs and add vertices
	VertexBuffers vertexBuffers(1); 
	VAOManager vaoManager(1);       

	// First triangle setup
	vaoManager.BindVAO(); // Bind the first VAO
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER); // Bind the first VBO
	vertexBuffers.AddVertices(vertices, sizeof(vertices)); // Add vertices to the first VBO
	vaoManager.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	vaoManager.SetAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vaoManager.SetAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// create texture manager and load texture
	TextureManager textureManager(1);
	textureManager.FlipTexture();
	textureManager.BindTexture();
	textureManager.LoadTexture("C:/Users/Thomas/Downloads/container2.png");
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	textureManager.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textureManager.ActivateTexture(0);

	TextureManager textureSpecular(1);
	textureSpecular.FlipTexture();
	textureSpecular.BindTexture();
	textureSpecular.LoadTexture("C:/Users/Thomas/Downloads/container2_specular.png");
	textureSpecular.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	textureSpecular.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	textureSpecular.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	textureSpecular.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textureSpecular.ActivateTexture(1);

	TextureManager textureEmission(1);
	textureEmission.FlipTexture();
	textureEmission.BindTexture();
	textureEmission.LoadTexture("C:/Users/Thomas/Downloads/matrix.jpg");
	textureEmission.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	textureEmission.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	textureEmission.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	textureEmission.SetTextureWrappingAndFiltering(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textureEmission.ActivateTexture(2);



	// create second vao for the second cube
	VAOManager vaoManager2(1);
	vaoManager2.BindVAO();
	vertexBuffers.BindVertexBuffers(GL_ARRAY_BUFFER);
	vertexBuffers.AddVertices(vertices, sizeof(vertices));
	vaoManager2.SetAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));

	






	// X. Create and compile the vertex shader
	Shader shader;
	Shader lightSourceShader;

	GLint vertexShader = shader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Vertex.vert");
	GLint fragmentShader = shader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/Fragment.frag");
	shader.CreateShaderProgram(vertexShader, fragmentShader);
	shader.UseShaderProgram();
	shader.setInt("material.diffuse", 0); // -1 which becomes 0
	shader.setInt("material.specular", 1); // -1 which becomes 1
	//shader.setInt("material.emission", 2); // -1 which becomes 2


	GLint lightVertexShader = lightSourceShader.CreateVertexShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/VertexLightSource.vert");
	GLint lightFragmentShader = lightSourceShader.CreateFragmentShader("C:/Users/Thomas/Desktop/school/SelfStudy/OpenGL/Projects/LearnOpenGL/LearnOpenGL/FragmentLightSource.frag");
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

		

		shader.UseShaderProgram();
		shader.setVec3("light.direction", -0.8f, -1.0f, -0.3f);
		shader.setVec3("viewPos", camera.Position);

		// set the light properties
		shader.setVec3("light.ambient", 0.05f, 0.05f, 0.05f); // shows how much light is in the scene
		shader.setVec3("light.diffuse", 0.2f, 0.2f, 0.2f); // shows the amount of light of shadows
		shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); // shows how shiny the light is
		shader.setVec3("light.direction", -0.2f, -1.0f, -0.3f); // direction of the light

		// set the material properties
		shader.setFloat("material.shininess", 32.0f);
		
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

		textureManager.ActivateTexture(0);
		textureSpecular.ActivateTexture(1);
		//textureEmission.ActivateTexture(2);

		// render the cube
		vaoManager.BindVAO();
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		


		// render the second cube
		// copy the projection and view from the first cube so the second cube is in the same view
		/*lightSourceShader.UseShaderProgram();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", view);

		glm::mat4 lampModel = glm::mat4(1.0f);
		lampModel = glm::translate(lampModel, cubePositions[1]);
		lampModel = glm::rotate(lampModel, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));


		lampModel = glm::scale(lampModel, glm::vec3(0.15f));
		lightSourceShader.setMat4("model", lampModel);

		vaoManager2.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		window.swapBuffersAndPollEvents();
	}
	window.~WindowManager();
	
	
	return 0;
}

