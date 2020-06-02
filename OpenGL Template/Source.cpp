#include <glew.h>
#include <glfw3.h>



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

	while (!glfwWindowShouldClose(Window)) {
				/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

				/* Swap front and back buffers */
		glfwSwapBuffers(Window);

				/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
}