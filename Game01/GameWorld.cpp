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
	this->terrainShader = new TerrainShader();
	this->renderer = new Renderer(*(this->shader), *this->terrainShader, *(this->display));

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
	this->camera = new Camera(glm::vec3(0.0f, 10.0f, 0.0f), 10.0f, 0.0f, 0.0f);
	RawModel& m = OBJLoader::loadObjModel("plane.obj", *this->loader);
	ModelTexture& t = *(new ModelTexture(this->loader->loadTexture("res\\checker.png")));
	t.setReflectivity(5.0f);
	t.setShineDamper(10.f);

	TexturedModel& tm = *(new TexturedModel(t, m));

	this->cube = new Entity(tm, glm::vec3(0.0f, 10.0f, -20.0f), 0.0f, 0.0f, 0.0f, 0.5f);

	this->light = new Light(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(1, 1, 1));
	//ModelTexture& terrain_texture = *(new ModelTexture(this->loader->loadTexture("res\\wall.jpg")));
	//this->terrain = new Terrain(0, 0, *this->loader, terrain_texture);
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
	static float SPEED = 0.05f;
	glfwPollEvents();
	
	if (glfwGetKey(this->window, GLFW_KEY_W)) {
		this->camera->increasePosZ(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		this->camera->increasePosZ(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		this->camera->increasePosX(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		this->camera->increasePosX(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
		this->camera->increasePosY(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
		this->camera->increasePosY(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		this->camera->increasePitch(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		this->camera->increasePitch(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		this->camera->increaseYaw(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		this->camera->increaseYaw(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_G)) {
		this->light->increasePosX(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_H)) {
		this->light->increasePosX(-SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_V)) {
		this->light->increasePosY(SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_B)) {
		this->light->increasePosY(-SPEED);
	}



}

void GameWorld::update()
{
}

void GameWorld::render()
{
	this->cube->increaseRotation(0.0f, 0.1f, 0.0f);

	this->shader->startShader();
	//this->terrainShader->startShader();
	this->shader->loadLight(*this->light);
	/* Render here */
	this->renderer->prepare();

	this->shader->loadViewlMatrix(*this->camera);

	this->renderer->render(*this->cube);

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
	this->shader->stopShader();
	//this->terrainShader->stopShader();

}
