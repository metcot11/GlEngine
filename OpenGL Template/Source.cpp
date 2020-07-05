#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "assimp/config.h"

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

int main(void) {


	glfwInit();

			/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* Window = glfwCreateWindow(Window_Width, Window_Heigth, "Window", NULL, NULL);

	glfwMakeContextCurrent(Window);

	glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
	glfwSetCursorPosCallback(Window, Mouse_CallBack);
	glfwSetScrollCallback(Window, scroll_CallBack);
		
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	FlipTextures();

	if (glewInit() != GLEW_OK)
		return -1;
		/*Setting up ImGui*/
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Window, true);
	ImGui::StyleColorsClassic();


	Shader shader("Shader/ModelLoader/fModel.Shader", "Shader/ModelLoader/vModel.Shader");
	Model _model("Model/Models/Backpack/backpack.obj");

	while (!glfwWindowShouldClose(Window)){

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessImput(Window);

				/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplGlfwGL3_NewFrame();

		shader.On();

		shader.SetUniformVec3("viewPos", camera.GetCameraPos());
		
		camera.UpdateView(shader);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shader.SetUniformMat4("model", model);
		_model.Draw(shader);


		glEnable(GL_DEPTH_TEST);

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
			StaticCursor = false;
		}else {
			glfwSetCursorPosCallback(window, Mouse_CallBack);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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