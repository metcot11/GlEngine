#pragma once
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

enum Movement
	{
		_Forward, _Backward, _Left, _Right
	};

class Camera
{
public:
	const float YAW			= -90.0f;
	const float PITCH		= 0.0f;
	const float SPEED		= 5.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM		= 45.0f;
	const int Window_Width  = 1240;
	const int Window_Heigth = 640;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
public:
	Camera();

	void ProcessKeyBoard(Movement MoveStats, float Delta);
	void ProcessMouse(float Xoffset, float Yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float Yoffset);

	void UpdateView(Shader shade);

	float Fov();

	glm::mat4 GetViewMatrix();
	glm::vec3 GetCameraPos();
private:
	void UpdateCameraVec();
};

