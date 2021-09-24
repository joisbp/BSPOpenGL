#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"

#include "Texture2D.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

#include "Scene.h"


static int WIDTH = 800;
static int HEIGHT = 600;
Camera cam(glm::vec3(0, 0, 10.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

void OnResize(GLFWwindow* window, int width, int height)
{
	// Resize the viewport
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, WIDTH, HEIGHT);
}

void ProcessInput(GLFWwindow* window, Camera* cam, float deltaTime)
{
	// If escape key is pressed, send the signal to close the window and stop
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	cam->UpdateCamera(window, deltaTime);
}

void UpdateMousePosition(GLFWwindow* window, double xpos, double ypos)
{
	cam.UpdateCameraView(xpos, ypos);
}

void LogGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		return;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "Error in Line" << (int)userParam << std::endl;
		std::cout << message << std::endl;
		__debugbreak();
	}
}

int main()
{
	//Initializing GLFW and Setting OPENGL Versions to use
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "BSPRenderingEngine", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate();
		return -1;
	}


	// Making the current window as render context
	glfwMakeContextCurrent(window);


	//Initializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, UpdateMousePosition);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	glDebugMessageCallback(LogGLDebugMessage, (void*)__LINE__);

	//Creating viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	//Setting up callback function to call when window is resized
	glfwSetFramebufferSizeCallback(window, OnResize);


	{
		Shader shader("Basic.shader");
		Shader redShader("Red.shader");
		Shader modelShader("Model.shader");

		Texture2D texContainer("Models/backpack/specular.jpg", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		Texture2D texFace("Textures/awesomeface.png", GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE);
		// Render a Triangle
		float vertices[16] = {
								-0.25f, -0.25f, 0.0f, 0.0f, //v0	0X00
								0.25f, -0.25f, 1.0f, 0.0f,	//v1	16
								0.25f, 0.25f, 1.0f, 1.0f,	//v2	32
								-0.25f, 0.25f, 0.0f, 1.0f	//v3	48
		};

		unsigned int indices[6] = { 0, 1, 3, 3, 1, 2 };

		// Vertex Buffer Object

		VertexBuffer vb(sizeof(vertices), vertices);
		IndexBuffer ib(sizeof(indices), indices);

		VertexArray va;
		VertexLayout vl;

		vl.PushAttribute<float>(2);
		vl.PushAttribute<float>(2);

		va.AddLayout(vl, vb);


		Scene scene;
		scene.LoadSceneFromFile("Models/backpack/backpack.obj");


#include "Cube.h"

		VertexBuffer cubeVB(sizeof(cVertices), cVertices);
		IndexBuffer cubeIB(sizeof(cIndices), cIndices);

		VertexArray cVA;
		VertexLayout cVL;

		cVL.PushAttribute<float>(3);
		cVL.PushAttribute<float>(2);

		cVA.AddLayout(cVL, cubeVB);

		shader.Bind();

		texContainer.Bind(0);
		texFace.Bind(1);

		shader.SetUniform1("sampleTexture", 0);
		shader.SetUniform1("faceTexture", 1);

		//glm::mat4 rot = glm::mat4(1.0f);

		//rot = glm::rotate(rot, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//rot = glm::scale(rot, glm::vec3(2.f, 2.f, 2.f));
		////rot = glm::translate(rot, glm::vec3(0.2f, 0.0f, 0.f));

		//shader.SetMatrix4("rot", rot);


		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

		shader.SetMatrix4("proj", proj);

		float deltaTime = 0.0f;
		float lastTime = 0.0f;


		//Main Rendering Loop
		while (!glfwWindowShouldClose(window))
		{
			shader.Bind();
			texContainer.Bind(0);

			float currTime = glfwGetTime();
			deltaTime = currTime - lastTime;
			lastTime = currTime;

			ProcessInput(window, &cam, deltaTime);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cVA.Bind();
			cubeIB.Bind();


			shader.SetUniform4f("color", 0.1f, 0.2f, 0.7f, 1.0f);

			glm::mat4 rot = glm::mat4(1.0f);

			rot = glm::rotate(rot, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			//rot = glm::scale(rot, glm::vec3(2.f, 2.f, 2.f));

			shader.SetMatrix4("world", rot);

			cam.UpdateShader(&shader);

			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

			shader.UnBind();

			modelShader.Bind();

			cam.UpdateShader(&modelShader);
			modelShader.SetMatrix4("proj", proj);
			modelShader.SetMatrix4("world", rot);

			modelShader.SetUniform3f("ambientColor", 1.0f, 1.0f, 1.0f);
			modelShader.SetUniform1f("ambientCoeff", 0.1f);

			// Direction Light
			modelShader.SetUniform3f("dLight.Direction", -0.2f, -1.0f, -0.3f);
			modelShader.SetUniform3f("dLight.ambient", 0.02f, 0.03f, 0.2f);
			modelShader.SetUniform3f("dLight.diffuse", 0.7f, 0.7f, 0.8f);
			modelShader.SetUniform3f("dLight.specular", 1.0f, 1.0f, 1.0f);

			// Point Light
			modelShader.SetUniform3f("pLight[0].Position", 2.3f, -0.3f, -1.0f);
			modelShader.SetUniform3f("pLight[0].ambient", 0.05f, 0.05f, 0.05f);
			modelShader.SetUniform3f("pLight[0].diffuse", 1.0f, 0.02f, 0.2f);
			modelShader.SetUniform3f("pLight[0].specular", 1.0f, 1.0f, 1.0f);
			modelShader.SetUniform1f("pLight[0].constant", 1.0f);
			modelShader.SetUniform1f("pLight[0].linear", 0.09);
			modelShader.SetUniform1f("pLight[0].quadratic", 0.032);

			modelShader.SetUniform3f("pLight[1].Position", -2.3f, -0.3f, -1.0f);
			modelShader.SetUniform3f("pLight[1].ambient", 0.08f, 0.08f, 0.08f);
			modelShader.SetUniform3f("pLight[1].diffuse", 0.02f, 1.0f, 0.2f);
			modelShader.SetUniform3f("pLight[1].specular", 1.0f, 1.0f, 1.0f);
			modelShader.SetUniform1f("pLight[1].constant", 1.0f);
			modelShader.SetUniform1f("pLight[1].linear", 0.09);
			modelShader.SetUniform1f("pLight[1].quadratic", 0.032);

			//SpotLight
			modelShader.SetUniform3f("sLight.Position", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
			modelShader.SetUniform3f("sLight.Direction", cam.GetForward().x, cam.GetForward().y, cam.GetForward().z);
			modelShader.SetUniform3f("sLight.ambient", 0.0f, 0.0f, 0.0f);
			modelShader.SetUniform3f("sLight.diffuse", 1.0f, 1.0f, 1.0f);
			modelShader.SetUniform3f("sLight.specular", 1.0f, 1.0f, 1.0f);
			modelShader.SetUniform1f("sLight.constant", 1.0f);
			modelShader.SetUniform1f("sLight.linear", 0.09);
			modelShader.SetUniform1f("sLight.quadratic", 0.032);
			modelShader.SetUniform1f("sLight.cutOff", glm::cos(glm::radians(12.5f)));
			modelShader.SetUniform1f("sLight.outerCutOff", glm::cos(glm::radians(15.0f)));
			//
			modelShader.SetUniform3f("viewPos", cam.GetPosition().x, cam.GetPosition().y, cam.GetPosition().z);
			scene.Draw(modelShader);
			modelShader.UnBind();


			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}
