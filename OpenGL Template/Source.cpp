#include <glew.h>
#include <glfw3.h>

#include"Textures/Texture Loader/stb_image.h"
#include "Shader.h"

#include <math.h>
#include <iostream>


int main(void) {


	glfwInit();


	const int Window_Width = 960;
	const int Window_Heigth = 540;
	int FrameBufferWidth = 0;
	int FrameBufferHeigth = 0;

			/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* Window = glfwCreateWindow(Window_Width, Window_Heigth, "Window", NULL, NULL);
	glfwMakeContextCurrent(Window);

	if (glewInit() != GLEW_OK)
		return -1;
		/* Rendering a triangule */
	float vertices[] = {
				/*Vertices*/		/*Colors*/		/*Texture*/
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

		/*Vertex buffer object*/
	unsigned int VBO;/*Vetex Buffer object ID*/

	glGenBuffers(1, &VBO);/*Creates the Vertex Buffer object in the GPU*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);/*assigning the data to the GPU*/


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

		/*Textres*/
	

	unsigned int Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);



	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	Shader shader("Shader/Fragment Shader.Shader", "Shader/Vertex Shader.Shader");
	shader.On();
	while (!glfwWindowShouldClose(Window)) {
				/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		glBindTexture(GL_TEXTURE_2D, Texture);

		shader.On();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				/* Swap front and back buffers */
		glfwSwapBuffers(Window);
				/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
}