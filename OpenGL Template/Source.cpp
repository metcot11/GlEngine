#include <glew.h>
#include <glfw3.h>
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
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
		/*Vertex buffer object*/
	unsigned int VBO;/*Vetex Buffer object ID*/

	glGenBuffers(1, &VBO);/*Creates the Vertex Buffer object in the GPU*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);/*assigning the data to the GPU*/

	Shader shader("Shader/Fragment Shader.Shader","Shader/Vertex Shader.Shader");
	shader.On();

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(Window)) {
				/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		glDrawArrays(GL_TRIANGLES, 0, 3);
				/* Swap front and back buffers */
		glfwSwapBuffers(Window);

		
		
				/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
}