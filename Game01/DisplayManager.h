#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

class DisplayManager
{
public:
	DisplayManager();
	~DisplayManager();
	GLFWwindow* createDisplay();
	void destroyDisplay();

private:
	GLFWwindow* window;
	unsigned int const DISP_WIDTH = 800;
	unsigned int const DISP_HEIGHT = 600;

	class FrameBufferSizeCallback {
		void operator()(GLFWwindow* window, int width, int height) {
			std::cout << "resize!" << std::endl;
			glViewport(0, 0, width, height);
		}
	};
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
