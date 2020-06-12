#include <glew.h>
#include <glfw3.h>

#include <iostream>

static const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* vertexShaderSource1 =
"#version 330 core\n"
"layout (location = 1) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
static const char* fragmentShaderSource1 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
//test branch 1

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

		/*Vertex Shader*/
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);/*Shader Id*/

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);/*Attaching the the shader to the object declered above*/
	glCompileShader(vertexShader);

		/*Shader Compile status*/
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		/*Fragment Shader*/
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
		/*Shader Program*/
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);

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