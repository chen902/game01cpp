#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	loadShader(VERTEX_SHADER_FILE, GL_VERTEX_SHADER);
	loadShader(FRAGMENT_SHADER_FILE, GL_FRAGMENT_SHADER);
}


ShaderProgram::~ShaderProgram()
{
}

unsigned int ShaderProgram::loadShader(const std::string & filepath, const GLenum & type)
{
	std::stringstream source;
	
	unsigned int shaderID = glCreateShader(type);
	
	std::fstream file(filepath);
	std::string line;
	
	// read shader sourcer from file
	while (std::getline(file, line)) {
		source << line;
	}

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

	return shaderID;
}
