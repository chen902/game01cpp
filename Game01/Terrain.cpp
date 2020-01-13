#include "Terrain.h"

static const float SIZE = 800.f;
static const int VERTEX_COUNT = 128;


Terrain::Terrain(int gridX, int gridZ, Loader & loader, ModelTexture texture) : x(gridX * SIZE), z(gridZ * SIZE), texture(texture)
{
	this->model = &this->generateTerrain(loader);
}

Terrain::~Terrain()
{
}

float Terrain::getX() const
{
	return this->x;
}

float Terrain::getZ() const
{
	return this->z;
}

RawModel & Terrain::getModel() const
{
	return *this->model;
}

ModelTexture & Terrain::getTexture() const
{
	return this->texture;
}

RawModel & Terrain::generateTerrain(Loader& loader)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	float* vertices = new float[count * 3];
	float* normals = new float[count * 3];
	float* textureCoords = new float[count * 2];
	unsigned int* indices = new unsigned int[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];
	int vertexPointer = 0;

	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(indices, 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1),
		vertices, count * 3,
		textureCoords, count * 2);
}
