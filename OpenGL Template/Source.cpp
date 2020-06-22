#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb.h"
#include "Shader.h"
#include "Camera/Camera.h"
#include "BufferObject.h"
#include "Renderer/Renderer.h"

#include "data.h"

#include <math.h>
#include <iostream>

void ProcessImput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos);
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset);

static const int Window_Width = 1240;
static const int Window_Heigth = 640;
int FrameBufferWidth = 0;
int FrameBufferHeigth = 0;

Camera Mouse;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

float lastX = Window_Width / 2.0f;
float lastY = Window_Heigth / 2.0f;

bool firstMouse = true;

float mixValue = 0.2f;

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


	unsigned int Texture1,Texture2;
	glGenTextures(1, &Texture1);
	glBindTexture(GL_TEXTURE_2D, Texture1); 
	
	
	int width, height, nrChannels;
	unsigned char* text = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
	
	if (text)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	
	glGenTextures(1, &Texture2);
	glBindTexture(GL_TEXTURE_2D, Texture2);
	
	text = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (text) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, text);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(text);
	}
	else {
		std::cout << "Failed to load texture2" << '\n';
	}
	



	Shader shader("Shader/Fragment Shader.Shader", "Shader/Vertex Shader.Shader");
	shader.On();

	shader.SetUniformInt("mTexture1", 0);
	shader.SetUniformInt("mTexture2", 1);
	Renderer R(shader, Mouse);
	R.GenCube(vertices2, sizeof(vertices2), indices, sizeof(indices));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	while (!glfwWindowShouldClose(Window)) {
				/* Render here */
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		shader.SetUniformFloat("scrol", mixValue);

		glEnable(GL_DEPTH_TEST);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture2);


		//glm::mat4 proj = glm::perspective(glm::radians(Mouse.Fov()), (float)Window_Width / (float)Window_Heigth, 0.1f, 100.0f);
		//
		//glm::mat4 view = Mouse.GetViewMatrix();
		//
		//
		//shader.SetUniformMat4("view", view);
		//shader.SetUniformMat4("projection", proj);
		//shader.On();
		//
		//buffer.BindVertexArrayBuffer("VAO2");
		//
		//
		//for (unsigned int i = 0; i < 11; i++)
		//{
		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f  * i;
		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	shader.SetUniformMat4("model", model);
		//
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}	
		for (int i = 0; i < 11; i++)
		{
			R.RenderRotatingCube(cubePositions[i], currentFrame);
		}
		ProcessImput(Window);
				/* Swap front and back buffers */
		glfwSwapBuffers(Window);
				/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
}

void ProcessImput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}

	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Mouse.ProcessKeyBoard(_Forward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Mouse.ProcessKeyBoard(_Backward, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Mouse.ProcessKeyBoard(_Left, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Mouse.ProcessKeyBoard(_Right, deltaTime);

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

	Mouse.ProcessMouse(XOffSet, YOffSet);
}
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse.ProcessMouseScroll((float)yoffset);
}