#include "Renderer.h"

Renderer::Renderer(ShaderProgram& shader) : shader(shader)
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	creatProjectionMatrix();
	shader.startShader();
	loadProjectionMatrix();
	shader.stopShader();
}

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::render(const Entity& entity)
{
	glBindVertexArray(entity.getModel().getVaoID()); // bind vao
	glEnableVertexAttribArray(0);
	
	// positions the entity in the 3d world
	glm::mat4 modelMatrix = Transformations::createModelMatrix(entity);
	shader.loadModelMatrix(modelMatrix);

	glDrawElements(GL_TRIANGLES, entity.getModel().getVerticesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind vao
}

void Renderer::creatProjectionMatrix()
{
	// TODO: figure away to the the windows size here	
	projection = glm::perspective(glm::radians(45.5f),  1024.0f/ 768.0f , 0.1f, 100.0f);
}

void Renderer::loadProjectionMatrix()
{
	shader.loadProjectionMatrix(projection);
}
