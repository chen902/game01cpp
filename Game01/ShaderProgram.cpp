#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	vertexShaderID = loadShader(VERTEX_SHADER_FILE, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(FRAGMENT_SHADER_FILE, GL_FRAGMENT_SHADER);
	programID = createProgram();
}


ShaderProgram::~ShaderProgram()
{
}

unsigned int ShaderProgram::loadShader(const std::string & filepath, const GLenum & type)
{
	std::stringstream source;
	
	unsigned int shaderID = glCreateShader(type);
	
	std::fstream file;

	try{
		file.open(filepath);
	}
	catch (std::exception e){
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

unsigned int ShaderProgram::createProgram()
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

void ShaderProgram::startShader()
{
	glUseProgram(programID);
}

void ShaderProgram::stopShader()
{
	glUseProgram(0);
}
