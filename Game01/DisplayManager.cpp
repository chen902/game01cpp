#include "DisplayManager.h"

int DisplayManager::curr_width = 0;
int DisplayManager::curr_height = 0;

DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
	
}

GLFWwindow* DisplayManager::createDisplay()
{
	DisplayManager::curr_width = DISP_WIDTH;
	DisplayManager::curr_height = DISP_HEIGHT;

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
	glViewport(0, 0, DISP_WIDTH, DISP_HEIGHT);
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
	DisplayManager::curr_width = width;
	DisplayManager::curr_height = height;

	std::cout << "width: " << width << " height: " << height << std::endl;
	glViewport(0, 0, width, height);
}
