#include "GameWorld.h"



GameWorld::GameWorld()
{

}


GameWorld::~GameWorld()
{
}

void GameWorld::init()
{
	this->display = new DisplayManager();
	this->window = this->display->createDisplay();

	// initialize glew
	GLenum err = glewInit();

	this->loader = new Loader();
	this->shader = new ShaderProgram();
	this->renderer = new Renderer(*(this->shader), *(this->display));

	this->createEntities();
}

void GameWorld::run()
{
	this->mainLoop();
	this->stop();
}

void GameWorld::stop()
{
	this->loader->cleanUp();
	this->display->destroyDisplay();
}

void GameWorld::createEntities()
{
	this->camera = new Camera(glm::vec3(0.0f, 0.5f, 30.0f), 10.0f, 0.0f, 1.0f);
	RawModel& m = OBJLoader::loadObjModel("cube.obj", *this->loader);
	ModelTexture& t = *(new ModelTexture(this->loader->loadTexture("res\\wall.jpg")));

	TexturedModel& tm = *(new TexturedModel(t, m));

	this->cube = new Entity(tm, glm::vec3(0.0f, 0.0f, 0.0f), -55.0f, 0.0f, 0.0f, 0.5f);

}

void GameWorld::mainLoop()
{
	while (!glfwWindowShouldClose(this->window))
	{
		this->handleUserInput();
		this->update();
		this->render();
	}
}

void GameWorld::handleUserInput()
{
}

void GameWorld::update()
{
}

void GameWorld::render()
{
	this->cube->increaseRotation(0.0f, 0.1f, 0.0f);

	this->shader->startShader();
	/* Render here */
	this->renderer->prepare();

	this->shader->loadViewlMatrix(*this->camera);

	this->renderer->render(*this->cube);
	//this->renderer->render(floor_entity);
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
	this->shader->stopShader();

}
