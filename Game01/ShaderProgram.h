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

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	unsigned int loadShader(const std::string& filepath, const GLenum& type);
	unsigned int createProgram();
	void startShader();
	void stopShader();
	void loadViewlMatrix(const Camera& camera) const;
	void loadModelMatrix(const glm::mat4& matrix) const;
	void loadProjectionMatrix(const glm::mat4& matrix) const;
	void getAllUniformLocations();

	//getters
	unsigned int getProgramID() const { return programID; }

private:
	Logger logger = Logger("ShaderProgram");
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	int locationModelMatrix;
	int locationViewMatrix;
	int locationProjectionMatrix;
	
	const char* VERTEX_SHADER_FILE = "vertexShader.txt";
	const char* FRAGMENT_SHADER_FILE = "fragmentShader.txt";

	// private methods
	int getUniformLocation(const std::string& name);
	void loadMatrix(int location, const glm::mat4& matrix) const;
};

