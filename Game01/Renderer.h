#pragma once
#include "RawModel.h"
#include "ShaderProgram.h"
#include "TerrainShader.h"
#include "Entity.h"
#include "Terrain.h"
#include "DisplayManager.h"
#include <GLFW/glfw3.h>
#include <vector>

class Renderer
{
public:
	Renderer(ShaderProgram& shader,TerrainShader& terrainShader, const DisplayManager& display);
	~Renderer();
	void prepare();
	void render(const Entity& entity);
	void render(const Terrain& t);

private:
	glm::mat4 projection;
	ShaderProgram& shader;
	TerrainShader& terrainShader;
	const DisplayManager& display;

	void creatProjectionMatrix();
	void loadProjectionMatrix();
};

