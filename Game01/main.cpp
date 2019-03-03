#include <GLFW/glfw3.h>
#include "DisplayManager.h"
#include "Renderer.h"

int main(void)
{
	DisplayManager display;
	GLFWwindow* window = display.createDisplay();
	
	Renderer renderer;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.prepare();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	display.destroyDisplay();

	return 0;
}