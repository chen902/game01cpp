#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DisplayManager.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Logger.h"

int main(void)
{
	Logger logger = Logger("Main");
	
	DisplayManager display;
	GLFWwindow* window = display.createDisplay();
	
	Renderer renderer;
	
	// initialize glew
	GLenum err = glewInit();

	const GLubyte* ver = glGetString(GL_SHADING_LANGUAGE_VERSION);
	ShaderProgram shader;

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