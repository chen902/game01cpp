#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DisplayManager.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Logger.h"
#include "Loader.h"
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

int main(void)
{
	Logger logger = Logger("Main");
	
	// handles window opening
	DisplayManager display;
	GLFWwindow* window = display.createDisplay();

	// initialize glew
	GLenum err = glewInit();

	// initialize rendering stuff
	
	Loader loader;
	ShaderProgram shader;
	Renderer renderer(shader, display);

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	 -0.5f, -0.5f, 0.0f,  // bottom left
	 -0.5f,  0.5f, 0.0f   // top left 
	};
	
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	RawModel& model = loader.loadToVAO(indices, sizeof(indices), vertices, sizeof(vertices));
	//RawModel& model2 = loader.loadToVAO(indices, sizeof(indices), vertices2, sizeof(vertices2));

	Entity entity(model, glm::vec3(0.0f, 0.0f, 0.0f));

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		shader.startShader();
		/* Render here */
		renderer.prepare();

		shader.loadViewlMatrix(camera);

		renderer.render(entity);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		shader.stopShader();
	}

	loader.cleanUp();
	display.destroyDisplay();

	logger.stop();
	return 0;
}