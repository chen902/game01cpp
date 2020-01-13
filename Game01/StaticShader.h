#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Logger.h"

class StaticShader
{
public:
	StaticShader();
	~StaticShader();
	void startShader();
	void stopShader();

protected:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;

	Logger logger = Logger("StaticShader");
	unsigned int loadShader(const std::string & filepath, const GLenum & type);
	unsigned int createProgram();
	int getUniformLocation(const std::string & name);
	void loadMatrix(int location, const glm::mat4 & matrix) const;
};

