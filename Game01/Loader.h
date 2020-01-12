#pragma once
/* Loads 3D models from file to GPU memory */
#include <GL/glew.h>
#include "RawModel.h"
#include <list>
#include "Logger.h"

#include "stb_image.h"


class Loader
{
public:
	~Loader();
	
	RawModel& loadToVAO(const unsigned int* indices, size_t indicesSize, const float* vertices, size_t verticesSize, const float* textureCoordinates, size_t textureCoordSize);
	unsigned int loadTexture(const std::string& filepath);
	unsigned int createVAO();
	void bindIndicesBuffer(const unsigned int* indices, size_t indicesSize);
	void storeDataInAttribList(const int& attribNum, const size_t& stride, const float* data, const size_t& dataSize);
	void unbindVAO();
	void cleanUp();

private:
	Logger logger = Logger("Loader");
	std::list<unsigned int> vaos;
	std::list<unsigned int> vbos;
};

