#pragma once
#include "StaticShader.h"
#include "Camera.h"
#include "Transformations.hpp"

class TerrainShader : public StaticShader
{
public:
	TerrainShader();
	~TerrainShader();
	void loadViewlMatrix(const Camera& camera) const;
	void loadModelMatrix(const glm::mat4& matrix) const;
	void loadProjectionMatrix(const glm::mat4& matrix) const;
	void getAllUniformLocations();

	//getters
	unsigned int getProgramID() const { return programID; }

private:
	Logger logger = Logger("TerrainShader");

	int locationModelMatrix;
	int locationViewMatrix;
	int locationProjectionMatrix;

	const char* VERTEX_SHADER_FILE = "terrainVertexShader.txt";
	const char* FRAGMENT_SHADER_FILE = "terrainFragmentShader.txt";
};

