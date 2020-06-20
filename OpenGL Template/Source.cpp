#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Textures/Texture Loader/stb_image.h"
#include "Shader.h"
#include "Camera/Camera.h"
#include "BufferObject.h"

#include "vertices.h"

#include <math.h>
#include <iostream>

void ProcessImput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos);
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset);

const int Window_Width = 1240;
const int Window_Heigth = 640;
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

	float vertices[] = {
				/*Vertices*/		/*Colors*/		/*Texture1*/
		 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,		
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3 
	};

	BufferObject buffer;

	buffer.CreateVertexArrayBuffer("VAO");
	buffer.BindVertexArrayBuffer("VAO");


	buffer.CreateVertexBuffer(sizeof(vertices2), vertices2, "Cube");
	buffer.BindVertexBuffer("Cube");

	buffer.CreateElementBuffer(sizeof(indices), indices, "Indices");
	buffer.BindElementBuffer("Indices");


	buffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	buffer.AttribPointer(1, 3, GL_FLOAT, 8, 3);
	buffer.AttribPointer(2, 2, GL_FLOAT, 8, 6);

	buffer.UnBindVertexArrayBuffer();

	buffer.CreateVertexArrayBuffer("VAO2");
	buffer.BindVertexArrayBuffer("VAO2");

	buffer.AttribPointer(0, 3, GL_FLOAT, 5, 0);
	buffer.AttribPointer(1, 2, GL_FLOAT, 5, 3);

	buffer.UnBindVertexArrayBuffer();


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
	}
	else {
		std::cout << "Failed to load texture2" << '\n';
	}

	stbi_image_free(text);


	Shader shader("Shader/Fragment Shader.Shader", "Shader/Vertex Shader.Shader");
	shader.On();

	shader.SetUniformInt("mTexture1", 0);
	shader.SetUniformInt("mTexture2", 1);
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	while (!glfwWindowShouldClose(Window)) {
				/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		shader.SetUniformFloat("scrol", mixValue);

		glEnable(GL_DEPTH_TEST);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture2);

		glm::mat4 proj = glm::perspective(glm::radians(Mouse.Fov()), (float)Window_Width / (float)Window_Heigth, 0.1f, 100.0f);
		
		glm::mat4 view = Mouse.GetViewMatrix();;

	
		shader.SetUniformMat4("view", view);
		shader.SetUniformMat4("projection", proj);
		shader.On();

		buffer.BindVertexArrayBuffer("VAO2");


		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (i % 3 == 0) {
				angle = (float)glfwGetTime() * 25.0f;
			}
			else if (i % 2 == 0) {
				angle = (float)glfwGetTime() * -50.0f;
			}
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniformMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		

		ProcessImput(Window);
				/* Swap front and back buffers */
		glfwSwapBuffers(Window);
				/* Poll for and process events */
		glfwPollEvents();
	}
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
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
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	
	float XOffSet = xPos - lastX;
	float YOffSet = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	Mouse.ProcessMouse(XOffSet, YOffSet);
}
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Mouse.ProcessMouseScroll(yoffset);
}