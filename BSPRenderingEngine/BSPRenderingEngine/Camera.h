#pragma once

#include "glm/glm.hpp"
#include "Graphics.h"

class Shader;
class Camera
{
private:
	glm::vec3 m_LookAtTarget;
	glm::vec3 m_Position;
	glm::vec3 m_UpVector;
	glm::vec3 m_FrontVector;

	float m_MoveSpeed;
	float m_MouseSensitivity;

	float m_Yaw, m_Pitch;

	float prevMouseXPosition, prevMouseYPosition;

	bool m_FirstMouse;
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	~Camera();

	void UpdateCamera(GLFWwindow* window, float deltaTime);

	void UpdateCameraView(float xPosition, float yPosition);

	glm::mat4 GetViewMatrix();

	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::vec3 GetLookAt() const { return m_LookAtTarget; }
	inline glm::vec3 GetUp() const { return m_UpVector; }
	inline glm::vec3 GetForward() const { return m_FrontVector; }

	void UpdateShader(Shader* shader);
};

