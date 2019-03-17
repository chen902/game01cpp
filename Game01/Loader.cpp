#include "Loader.h"

Loader::~Loader()
{
}

RawModel & Loader::loadToVAO(const unsigned int* indices, size_t indicesSize, const float * vertices, size_t verticesSize)
{
	// create and bind
	unsigned int vao = createVAO();
	bindIndicesBuffer(indices, indicesSize);
	storeDataInAttribList(0, 3, vertices, verticesSize);
	unbindVAO();
	return *(new RawModel(vao, indicesSize / sizeof(unsigned int)));  // indicesSize / sizeof(unsigned int) = actual number of vertices rendered
}

unsigned int Loader::createVAO()
{
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

void Loader::bindIndicesBuffer(const unsigned int* indices, size_t indicesSize)
{
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	
	// no need to unbind because unbind vao will take care of that??
	
	vbos.push_back(ebo);
}

void Loader::storeDataInAttribList(const int & attribNum, const size_t & stride, const float * data, const size_t & dataSize)
{
	logger.debug("Storing data in attribute number " + std::to_string(attribNum));
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attribNum, stride, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attribNum);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::cleanUp()
{
	logger.debug("cleaning up..");
	for (unsigned int vao : vaos) 
		glDeleteVertexArrays(1, &vao);
	
	for (unsigned int vbo : vbos)
		glDeleteBuffers(1, &vbo);
}
