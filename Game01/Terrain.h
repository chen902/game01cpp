#pragma once
#include "RawModel.h"
#include "ModelTexture.h"
#include "Loader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader& loader, ModelTexture texture);
	~Terrain();

	float getX() const;
	float getZ() const;
	RawModel& getModel() const;
	ModelTexture& getTexture() const;

private:
	float x;
	float z;
	RawModel* model;
	ModelTexture& texture;
	
	RawModel& generateTerrain(Loader& loader);
};

