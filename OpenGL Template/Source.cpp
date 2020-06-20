#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"Textures/Texture Loader/stb_image.h"
#include "Shader.h"
#include "Camera/Camera.h"

#include "vertices.h"

#include <math.h>
#include <iostream>

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
float Fov = 45.0f;
float lastX = 800 / 2;
float lastY = 600 / 2;

bool firstMouse = true;

void ProcessImput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos);
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset);

float mixValue = 0.2f;
const int Window_Width = 1240;
const int Window_Heigth = 640;
int FrameBufferWidth = 0;
int FrameBufferHeigth = 0;

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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


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

		shader.SetUniformFloat("scrol", mixValue);

		glEnable(GL_DEPTH_TEST);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture2);

		glm::mat4 proj = glm::perspective(glm::radians(Fov), (float)Window_Width / (float)Window_Heigth, 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	
		shader.SetUniformMat4("view", view);
		shader.SetUniformMat4("projection", proj);
		shader.On();
		glBindVertexArray(VAO2);


		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (i % 3 == 0) {
				angle = glfwGetTime() * 25.0f;
			}
			else if (i % 2 == 0) {
				angle = glfwGetTime() * -50.0f;
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
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Mouse_CallBack(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // initially set to true
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	
	float XOffSet = xPos - lastX;
	float YOffSet = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	const float Sensitivity = 0.1f;
	XOffSet *= Sensitivity;
	YOffSet *= Sensitivity;

	yaw	  += XOffSet;
	pitch += YOffSet;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 Direction;
	Direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Direction.y = sin(glm::radians(pitch));
	Direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(Direction);

}
void scroll_CallBack(GLFWwindow* window, double xoffset, double yoffset)
{
	Fov -= (float)yoffset;
	if (Fov < 1.0f)
		Fov = 1.0f;
	if (Fov > 45.0f)
		Fov = 45.0f;
}