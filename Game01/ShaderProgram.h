#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL/glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	unsigned int loadShader(const std::string& filepath, const GLenum& type);

private:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	
	const char* VERTEX_SHADER_FILE = "vertexShader.txt";
	const char* FRAGMENT_SHADER_FILE = "fragmentShader.txt";
};

