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


static int WIDTH = 800;
static int HEIGHT = 600;

void OnResize(GLFWwindow* window, int width, int height)
{
	// Resize the viewport
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, WIDTH, HEIGHT);
}

void ProcessInput(GLFWwindow* window)
{
	// If escape key is pressed, send the signal to close the window and stop
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
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

		Texture2D texContainer("Textures/container.jpg", GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
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

		va.Bind();
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

		//Main Rendering Loop
		while (!glfwWindowShouldClose(window))
		{
			ProcessInput(window);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			ib.Bind();


			shader.SetUniform4("color", 0.1f, 0.2f, 0.7f, 1.0f);

			glm::mat4 rot = glm::mat4(1.0f);

			rot = glm::rotate(rot, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			rot = glm::scale(rot, glm::vec3(2.f, 2.f, 2.f));

			shader.SetMatrix4("rot", rot);


			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}
