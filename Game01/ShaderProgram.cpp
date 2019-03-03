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

	const char* source_c = source.str().c_str();

	// bind shader source
	glShaderSource(shaderID, 1, &source_c, NULL);

	// compile current shader
	glCompileShader(shaderID);
	
	int  success;
	char infoLog[512];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "error compiling shader!" << std::endl << infoLog << std::endl;
		return -1;
	}

	return shaderID;

}
