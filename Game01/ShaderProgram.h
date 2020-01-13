#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Logger.h"
#include <GL/glew.h>
#include "Entity.h"
#include "Transformations.hpp"
#include "StaticShader.h"

class ShaderProgram: public StaticShader
{
public:
	ShaderProgram();
	~ShaderProgram();
	void loadViewlMatrix(const Camera& camera) const;
	void loadModelMatrix(const glm::mat4& matrix) const;
	void loadProjectionMatrix(const glm::mat4& matrix) const;
	void getAllUniformLocations();

	//getters
	unsigned int getProgramID() const { return programID; }

private:
	Logger logger = Logger("ShaderProgram");

	int locationModelMatrix;
	int locationViewMatrix;
	int locationProjectionMatrix;
	
	const char* VERTEX_SHADER_FILE = "vertexShader.txt";
	const char* FRAGMENT_SHADER_FILE = "fragmentShader.txt";
};

