#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
	: m_Position(position), m_LookAtTarget(target), m_UpVector(up), m_MoveSpeed(10), m_FrontVector(0,0,-1.0f), m_Yaw(-90.0f), m_Pitch(0.0f), m_FirstMouse(true),
	m_MouseSensitivity(0.1f)
{

}

Camera::~Camera()
{}

void Camera::UpdateCamera(GLFWwindow* window, float deltaTime)
{
	glm::vec3 direction(0.0f);
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)) * deltaTime;
	direction.y = sin(glm::radians(m_Pitch)) * deltaTime ;
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)) * deltaTime;

	m_FrontVector =  glm::normalize(direction);
	glm::vec3 Right = glm::normalize(glm::cross(m_FrontVector, glm::vec3(0, 1, 0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_UpVector = glm::normalize(glm::cross(Right, m_FrontVector));


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_MoveSpeed * deltaTime * m_FrontVector;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position -= m_MoveSpeed * deltaTime * m_FrontVector;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_MoveSpeed * deltaTime * glm::cross(m_FrontVector, m_UpVector);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position -= m_MoveSpeed * deltaTime * glm::cross(m_FrontVector, m_UpVector);
	}
}

void Camera::UpdateCameraView(float xPosition, float yPosition)
{
	if (m_FirstMouse)
	{
		prevMouseXPosition = xPosition;
		prevMouseYPosition = yPosition;
		m_FirstMouse = false;
	}

	float xOffset = (prevMouseXPosition - xPosition) * m_MouseSensitivity;
	float yOffset = (yPosition - prevMouseYPosition) * m_MouseSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;


	std::cout << m_Pitch << std::endl;

	prevMouseXPosition = xPosition;
	prevMouseYPosition = yPosition;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

void Camera::UpdateShader(Shader* shader)
{
	glm::mat4 view = GetViewMatrix();
	shader->SetMatrix4("view", view);
}
