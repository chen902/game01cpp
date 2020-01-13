#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Logger.h"
#include "Loader.h"
#include "DisplayManager.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Camera.h"
#include "OBJLoader.hpp"
#include "Terrain.h"
#include "Light.h"


class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void init();
	void run();
	void stop();

private:
	Logger logger = Logger("Main");
	
	DisplayManager* display;
	GLFWwindow* window;
	Loader* loader;
	ShaderProgram* shader;
	TerrainShader* terrainShader;
	Renderer* renderer;

	Camera* camera;

	Entity* cube;

	Terrain* terrain;
	Light* light;

	void createEntities();
	void mainLoop();
	void handleUserInput();
	void update();
	void render();
};

