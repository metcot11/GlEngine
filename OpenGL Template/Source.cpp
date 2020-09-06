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
void DrawCube(Shader shader, CubeMap texture, BufferObject& Buffer, glm::vec3 pos, float f);
void DrawCube(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos, float f);
void DrawPlane(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos);



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

	
	float size = 1;
	/*----------------plane--------------*/
	BufferObject planeBuffer(sizeof(PlaneData), PlaneData);
	planeBuffer.AttribPointer(0, 3, GL_FLOAT, 5, 0);
	planeBuffer.AttribPointer(1, 2, GL_FLOAT, 5, 3);
	/*----------------Box----------------*/
	BufferObject boxBuffer(sizeof(vertices), vertices);
	boxBuffer.AttribPointer(0, 3, GL_FLOAT, 8, 0);
	boxBuffer.AttribPointer(2, 3, GL_FLOAT, 8, 3);
	boxBuffer.AttribPointer(1, 2, GL_FLOAT, 8, 6);
	/*----------------Quad----------------------*/
	BufferObject quadBuffer(sizeof(quadVertices), quadVertices);
	quadBuffer.AttribPointer(0, 2, GL_FLOAT, 4, 0);
	quadBuffer.AttribPointer(1, 2, GL_FLOAT, 4, 2);
	/*--------------Skybox----------------------*/
	BufferObject skyboxBuffer(sizeof(skyboxVertices), skyboxVertices);
	skyboxBuffer.AttribPointer(0, 3, GL_FLOAT, 3, 0);

	//skyboxBuffer.UnBind();

	Shader shader("Shader/BasicShader/Basic.fshader", "Shader/BasicShader/Basic.vshader");
	Shader Modelshader("Shader/ModelLoader/fModel.Shader", "Shader/ModelLoader/vModel.Shader");
	Shader SingleColor("Shader/BasicShader/clearcolor.fShader", "Shader/BasicShader/Basic.vshader");
	Shader screenShader("Shader/Framebuffer/ScreenQuad.fshader","Shader/Framebuffer/ScreenQuad.vshader");
	Shader Shaderskybox("Shader/CubeMap/Skybox.fshader", "Shader/CubeMap/Skybox.vshader");
	
	std::vector<const char*> faces =
	{
		"Textures/Cubemap/skybox/right.jpg",
		"Textures/Cubemap/skybox/left.jpg",
		"Textures/Cubemap/skybox/top.jpg",
		"Textures/Cubemap/skybox/bottom.jpg",
		"Textures/Cubemap/skybox/front.jpg",
		"Textures/Cubemap/skybox/back.jpg"
	};
	CubeMap Skybox(faces);

	Texture Transparent("Textures/Tex_images/blending_transparent_window.png", "Texture", false);
	Texture texture("Textures/Tex_images/concrete.png", "Texture", true);
	Texture texture2("Textures/Tex_images/container.jpg", "Texture", true);
	
	unsigned int Framebuffer;
	glGenFramebuffers(1, &Framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);

	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window_Width, Window_Heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window_Width, Window_Heigth); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); 

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	FrameBuffer Frame;


	while (!glfwWindowShouldClose(Window)){

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessImput(Window);

		ImGui_ImplGlfwGL3_NewFrame();

				/* Render here */
		glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdateView(shader);

		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)Window_Width / (float)Window_Heigth, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

		/*----------------Cube-------------------*/
		DrawCube(shader, Skybox, boxBuffer, glm::vec3(5.0f, 0.02f, 5.0f), 1.0f);
		DrawCube(shader, Skybox, boxBuffer, glm::vec3(3.0f, 0.02f, 4.0f), 1.0f);
		/*----------------Plane-------------------*/
		DrawPlane(shader, texture, planeBuffer, glm::vec3(0.0f));
		glDepthFunc(GL_LEQUAL);
		Shaderskybox.On();
		Shaderskybox.SetUniformMat4("projection", proj);
		Shaderskybox.SetUniformMat4("view", view);
		skyboxBuffer.BindBuffer();
		
		Skybox.BindCubeMap(Shaderskybox, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		camera.UpdateView(shader);
		
		DrawCube(shader, Skybox, boxBuffer, glm::vec3(5.0f, 0.02f, 5.0f), 1.0f);
		DrawCube(shader, Skybox, boxBuffer, glm::vec3(3.0f, 0.02f, 4.0f), 1.0f);
	
		DrawPlane(shader, texture, planeBuffer, glm::vec3(0.0f));

		glDepthFunc(GL_LEQUAL);
		proj = glm::perspective(glm::radians(camera.Zoom), (float)Window_Width / (float)Window_Heigth, 0.1f, 100.0f);
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		Shaderskybox.On();
		Shaderskybox.SetUniformMat4("projection", proj);
		Shaderskybox.SetUniformMat4("view", view);
		skyboxBuffer.BindBuffer();
		Skybox.BindCubeMap(Shaderskybox, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);

		/*-----------Quad-----------------*/
		glDisable(GL_DEPTH_TEST);
		screenShader.On();
		quadBuffer.BindBuffer();
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	
		screenShader.SetUniformInt("texture1", 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		screenShader.Off();
		quadBuffer.UnBind();
		

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
void DrawCube(Shader shader, CubeMap texture, BufferObject& Buffer, glm::vec3 pos, float f) {
	shader.On();
	shader.SetUniformFloat("tex", true);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(f, f, f));

	shader.SetUniformVec3("cameraPos", camera.Position);
	shader.SetUniformMat4("model", model);
	texture.BindCubeMap(shader, 0);
	Buffer.BindBuffer();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	shader.Off();
}
void DrawCube(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos, float f) {
	shader.On();
	Buffer.BindBuffer();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(f, f, f));

	shader.SetUniformMat4("model", model);
	texture.BindTexture2D(shader, 1);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexBuffer();
	Buffer.UnBindVertexArrayBuffer();
	shader.Off();
}
void DrawPlane(Shader shader, Texture texture, BufferObject& Buffer, glm::vec3 pos) {
	shader.On();
	shader.SetUniformFloat("tex", false);
	Buffer.BindBuffer();
	shader.SetUniformMat4("model", glm::mat4(1.0f));
	texture.BindTexture2D(shader, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	Buffer.UnBindVertexArrayBuffer();
	Buffer.UnBindVertexBuffer();
	shader.Off();
}