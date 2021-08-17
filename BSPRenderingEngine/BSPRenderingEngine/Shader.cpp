#include "Shader.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const std::string& filePath)
	:m_ShaderID(0)
{
	ShaderSources sources = ParseShader(filePath);
	m_ShaderID = CreateShaderProgram(sources.vertexShader, sources.fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}


// Parse the Shader file and output a struct containing the source strings for vertex and fragment shader
ShaderSources Shader::ParseShader(const std::string& filePath)
{
	// Opening the file
	std::ifstream file(filePath);

	// Check if file is open
	if (!file.is_open())
	{
		return {};
	}

	std::string line;

	std::stringstream stream[2];
	int type = -1;

	// For each line
	while (getline(file, line))
	{
		// Check if the line starts with #shader for demarkation
		if (line.find("shader") != line.npos)
		{
			if (line.find("vertex") != line.npos)
			{
				type = 0;
			}

			if (line.find("fragment") != line.npos)
			{
				type = 1;
			}
		}
		else
		{
			// Keep pushing lines into the stream, Dont forget endl
			stream[type] << line << std::endl;
		}
	}
	

	return { stream[0].str(), stream[1].str() };
}

// Creating and Attaching and Linking the Shaders to the program
unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	// Check if it is successfull
	if (!success)
	{
		int length;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);

		char* messageLog = (char*)alloca(length);

		glGetProgramInfoLog(shaderProgram, length, &length, messageLog);
		std::cout << "Error in Linking Shaders" << std::endl;
		std::cout << messageLog;

		return 0;
	}

	glValidateProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);

	// Check if it is successfull
	if (!success)
	{
		int length;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);

		char *messageLog = (char*) alloca(length);

		glGetProgramInfoLog(shaderProgram, length, &length, messageLog);
		std::cout << "Error in Validating Shader" << std::endl;
		std::cout << messageLog;

		return 0;
	}

	// Delete the shaders, we dont need them any more
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

// Create and Compile the shader of give type and check if there are any errors in the source
unsigned int Shader::CompileShader(int shaderType, const std::string& shaderSource)
{
	unsigned int shader = glCreateShader(shaderType);

	const char* source = shaderSource.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		// We are stack allocating over heap allocating. If Heap Allocated delete the memory after use
		char* message = (char*) alloca(length);
		glGetShaderInfoLog(shader, length, &length, message);

		std::cout << "Error in " << (shaderType == GL_VERTEX_SHADER ? "VertexShader" : "FragmentShader ") << std::endl << message;

		return 0;
	}

	return shader;
}

// To use the current program before the draw call
void Shader::Bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4(const std::string& name, float r, float g, float b, float a)
{
	glUniform4f(GetLocation(name), r, g, b, a);
}

void Shader::SetUniform1(const std::string& name, int value)
{
	glUniform1i(GetLocation(name), value);
}

void Shader::SetMatrix4(const std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int Shader::GetLocation(const std::string& name)
{
	if (m_UniformMap.find(name) != m_UniformMap.end())
	{
		return m_UniformMap.at(name);
	}

	unsigned int location = glGetUniformLocation(m_ShaderID, name.c_str());

	if (location != unsigned int(-1))
	{
		m_UniformMap.insert({ name, location });
	}

	return location;
}
