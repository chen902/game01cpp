#include "Renderer.h"

Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::render(const RawModel & model, const ShaderProgram & shader)
{
	glBindVertexArray(model.getVaoID()); // bind vao
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, model.getVerticesCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind vao
}
