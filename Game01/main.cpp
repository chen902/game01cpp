#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DisplayManager.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Logger.h"
#include "Loader.h"

int main(void)
{
	Logger logger = Logger("Main");
	
	// handles window opening
	DisplayManager display;
	GLFWwindow* window = display.createDisplay();

	// initialize glew
	GLenum err = glewInit();

	// initialize rendering stuff
	Renderer renderer;
	Loader loader;
	ShaderProgram shader;

	float vertices[] = {
	 0.9f,  0.9f, 0.0f,  // top right
	 0.9f,  0.1f, 0.0f,  // bottom right
	 0.1f,  0.1f, 0.0f,  // bottom left
	 0.1f,  0.9f, 0.0f   // top left 
	};
	
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	float vertices2[] = {
	 -0.1f,  -0.1f, 0.0f,  // top right
	 -0.1f,  -0.9f, 0.0f,  // bottom right
	 -0.9f,  -0.9f, 0.0f,  // bottom left
	 -0.9f,  -0.1f, 0.0f   // top left 
	};

	RawModel& model = loader.loadToVAO(indices, sizeof(indices), vertices, sizeof(vertices));
	RawModel& model2 = loader.loadToVAO(indices, sizeof(indices), vertices2, sizeof(vertices2));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		shader.startShader();
		/* Render here */
		renderer.prepare();

		renderer.render(model, shader);
		renderer.render(model2, shader);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		shader.stopShader();
	}

	loader.cleanUp();
	display.destroyDisplay();

	return 0;
}