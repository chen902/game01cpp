#pragma once
#include "RawModel.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "DisplayManager.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer(ShaderProgram& shader, const DisplayManager& display);
	~Renderer();
	void prepare();
	void render(const Entity& entity);

private:
	glm::mat4 projection;
	ShaderProgram& shader;
	const DisplayManager& display;

	void creatProjectionMatrix();
	void loadProjectionMatrix();
};

