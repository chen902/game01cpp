#include "Loader.h"

Loader::~Loader()
{
}

RawModel & Loader::loadToVAO(const unsigned int* indices, size_t indicesSize, const float * vertices, size_t verticesSize, const float* textureCoordinates, size_t textureCoordSize, const float* normals, size_t normalsSize)
{
	// create and bind
	unsigned int vao = createVAO();
	bindIndicesBuffer(indices, indicesSize);
	storeDataInAttribList(0, 3, vertices, verticesSize);
	storeDataInAttribList(1, 2, textureCoordinates, textureCoordSize);
	storeDataInAttribList(2, 3, normals, normalsSize);
	unbindVAO();
	return *(new RawModel(vao, indicesSize / sizeof(unsigned int)));  // indicesSize / sizeof(unsigned int) = actual number of vertices rendered
}


unsigned int Loader::loadTexture(const std::string & filepath){
	
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		return -1;
	}

	stbi_image_free(data);
	

	return textureID;
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
	glVertexAttribPointer(attribNum, stride, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
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
