#pragma once
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

	enum Movement
	{
		_Forward, _Backward, _Left, _Right
	};

class Camera
{

private:
	const float YAW			= -90.0f;
	const float PITCH		=  0.0f;
	const float SPEED		=  2.5f;
	const float SENSITIVITY =  0.1f;
	const float ZOOM		=  45.0f;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float lastX = 800 / 2;
	float lastY = 600 / 2;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	bool FirstMouse;

public:


	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementspeed, float mousesensitivity);
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	Camera(float posx, float posy, float posz, float upx, float upy, float upz, float yaw, float pitch);
	Camera(float yaw, float pitch);
	Camera();
	

	void ProcessKeyBoard(Movement MoveStats, float Delta);
	void ProcessMouse(GLFWwindow* window, float Xpos, float Ypos, bool constrainPitch);
	void ProcessMouseScroll(float Yoffset);
	float Fov();
	glm::mat4 GetViewMatrix();
private:
	void UpdateCameraVec();
};

