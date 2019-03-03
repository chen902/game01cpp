#include "DisplayManager.h"



DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
	
}

GLFWwindow* DisplayManager::createDisplay()
{
	/* Initialize the library */
	if (!glfwInit())
		throw std::exception();

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(DISP_WIDTH, DISP_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw std::exception();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// get rid of this
	return this->window;
}

void DisplayManager::destroyDisplay()
{
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	std::cout << "resize!" << std::endl;
	glViewport(0, 0, width, height);
}
