#include "StaticShader.h"



StaticShader::StaticShader()
{
}


StaticShader::~StaticShader()
{
}

void StaticShader::startShader()
{
	glUseProgram(programID);
}

void StaticShader::stopShader()
{
	glUseProgram(0);
}

unsigned int StaticShader::loadShader(const std::string & filepath, const GLenum & type)
{

	std::stringstream source;

	unsigned int shaderID = glCreateShader(type);

	std::fstream file;

	try {
		file.open(filepath);
	}
	catch (std::exception e) {
		logger.error(e.what());
	}

	std::string line;

	// read shader sourcer from file
	while (std::getline(file, line)) {
		source << line << "\n";
	}

	file.close();

	std::string str_source = source.str();
	const char* source_c = str_source.c_str();

	// bind shader source
	glShaderSource(shaderID, 1, &source_c, NULL);

	// compile current shader
	glCompileShader(shaderID);

	int  success;
	char infoLog[512];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		logger.error("compiling shader failer!");
		logger.error(infoLog);
	}
	else
	{
		logger.info("shader compilation successfull.");
	}

	return shaderID;

}

unsigned int StaticShader::createProgram()
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShaderID);
	glAttachShader(shaderProgram, fragmentShaderID);
	glLinkProgram(shaderProgram);

	int success;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		char infoLog[512];
		logger.error("linking shader program failed!");
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		logger.error(infoLog);
		return -1;
	}

	// shaders should be deleted after linkage
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	logger.debug("linked shader program successfully!");

	return shaderProgram;

}

int StaticShader::getUniformLocation(const std::string & name)
{
	int location = glGetUniformLocation(programID, name.c_str());
	return location;
}

/* Loads a matrix to uniform with location in shader program */
void StaticShader::loadMatrix(int location, const glm::mat4 & matrix) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
