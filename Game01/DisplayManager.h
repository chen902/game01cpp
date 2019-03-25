#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

class DisplayManager
{
public:
	static int curr_width;
	static int curr_height;

	DisplayManager();
	~DisplayManager();
	GLFWwindow* createDisplay();
	void destroyDisplay();
	

private:
	GLFWwindow* window;
	unsigned int const DISP_WIDTH = 1024;
	unsigned int const DISP_HEIGHT = 768;
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
