#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "BufferObject.h"
#include "Lighting.h"
#include "Textures/Texture.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Model.h"
#include "Material.h"

#include <math.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <map>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw_gl3.h"


void ProcessImput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos);
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset);


static const int Window_Width = 1240;
static const int Window_Heigth = 640;
int FrameBufferWidth = 0;
int FrameBufferHeigth = 0;

Camera camera;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

float lastX = Window_Width / 2.0f;
float lastY = Window_Heigth / 2.0f;
bool firstMouse = true;
bool StaticCursor = true;
float lastCamYaw = 0;
float lastCamPitch = 0;

int main(void) {

	glfwInit();

			/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* Window = glfwCreateWindow(Window_Width, Window_Heigth, "Window", NULL, NULL);

	glfwMakeContextCurrent(Window);

	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(Window, Mouse_CallBack);
	glfwSetScrollCallback(Window, scroll_CallBack);
		
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (glewInit() != GLEW_OK)
		return -1;
		/*Setting up ImGui*/
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Window, true);
	ImGui::StyleColorsClassic();

	glEnable(GL_DEPTH_TEST);

	Renderer renderer(camera);

	while (!glfwWindowShouldClose(Window)){

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessImput(Window);

		ImGui_ImplGlfwGL3_NewFrame();

		/* Render here */

		renderer.UpdateFrame();

		/* Swap front and back buffers */

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(Window);
				/* Poll for and process events */
		glfwPollEvents();
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void ProcessImput(GLFWwindow* window)
{
		//Scape Window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
		//Free Mouse
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (StaticCursor) {
			glfwSetCursorPosCallback(window, nullptr);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			camera.Pitch = lastCamPitch;
			camera.Yaw = lastCamYaw;
			StaticCursor = false;
		}else {
			glfwSetCursorPosCallback(window, Mouse_CallBack);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			lastCamPitch = camera.Pitch;
			lastCamYaw = camera.Yaw;
			StaticCursor = true;
		}
	}

		//Move Control
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyBoard(_Forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyBoard(_Backward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyBoard(_Left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyBoard(_Right, deltaTime);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}
	
	float XOffSet = (float)xPos - lastX;
	float YOffSet = lastY - (float)yPos;
	lastX = (float)xPos;
	lastY = (float)yPos;

	camera.ProcessMouse(XOffSet, YOffSet);
}
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}
