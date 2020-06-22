#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpdateCameraVec();
}

void Camera::ProcessKeyBoard(Movement MoveStats, float Delta)
{
	float velocity = MovementSpeed * Delta;
	if (MoveStats == _Forward)
		Position += Front * velocity;

	if (MoveStats == _Backward)
		Position -= Front * velocity;

	if (MoveStats == _Left)
		Position -= Right * velocity;

	if (MoveStats == _Right)
		Position += Right * velocity;
}

void Camera::ProcessMouse(float Xoffset, float Yoffset)
{

	Xoffset *= MouseSensitivity;
	Yoffset *= MouseSensitivity;

	Yaw	  += Xoffset;
	Pitch += Yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	UpdateCameraVec();
}

void Camera::ProcessMouseScroll(float Yoffset)
{
	Zoom -= (float)Yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

float Camera::Fov()
{
	return Zoom;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateCameraVec()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp)); 
	Up = glm::normalize(glm::cross(Right, Front));
}

