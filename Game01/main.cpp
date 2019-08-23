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
#include "OBJLoader.hpp"

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

	RawModel& m = OBJLoader::loadObjModel("cube.obj", loader);
	
	Entity entity(m, glm::vec3(0.0f, 0.0f, 0.0f), -55.0f,0.0f,0.0f, 0.5f);

	Camera camera(glm::vec3(0.0f, 0.0f, 30.0f), 1.0f,1.0f,1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		entity.increaseRotation(0.0f, 0.1f, 0.0f);

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