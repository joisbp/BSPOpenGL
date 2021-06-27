#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "Shader.h"


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

		// Render a Triangle
		float vertices[8] = {
								-0.25f, -0.25f,
								0.25f, -0.25f,
								0.25f, 0.25f,
								-0.25f, 0.25f,
		};

		unsigned int indices[6] = { 0, 1, 3, 3, 1, 2 };

		// Vertex Buffer Object
		unsigned int VBO;
		glGenBuffers(1, &VBO);

		unsigned int elementBuffer;
		glGenBuffers(1, &elementBuffer);

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		shader.Bind();

		//Main Rendering Loop
		while (!glfwWindowShouldClose(window))
		{
			ProcessInput(window);

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);


			shader.SetUniform4("color", 0.1f, 0.2f, 0.7f, 1.0f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		//Terminating and cleaning up

		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &elementBuffer);
		glDeleteVertexArrays(1, &VAO);

	}

	glfwTerminate();
	return 0;
}
