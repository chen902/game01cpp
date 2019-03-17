#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	logger.debug("compiling vertex shader..");
	vertexShaderID = loadShader(VERTEX_SHADER_FILE, GL_VERTEX_SHADER);
	
	logger.debug("compiling fragment shader..");
	fragmentShaderID = loadShader(FRAGMENT_SHADER_FILE, GL_FRAGMENT_SHADER);
	
	logger.debug("linking shader program..");
	programID = createProgram();

	getAllUniformLocations();
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

void ShaderProgram::loadViewlMatrix(const Camera & camera) const
{
	glm::mat4 view = Transformations::createViewMatrix(camera);
	loadMatrix(locationViewMatrix, view);
}

void ShaderProgram::loadModelMatrix(const glm::mat4& matrix) const
{
	loadMatrix(locationModelMatrix, matrix);
}

void ShaderProgram::loadProjectionMatrix(const glm::mat4 & matrix) const
{
	loadMatrix(locationProjectionMatrix, matrix);
}

void ShaderProgram::getAllUniformLocations()
{
	locationModelMatrix = getUniformLocation("model_matrix");
	locationViewMatrix = getUniformLocation("view_matrix");
	locationProjectionMatrix = getUniformLocation("projection_matrix");
}

int ShaderProgram::getUniformLocation(const std::string & name)
{
	int location = glGetUniformLocation(programID, name.c_str());
	return location;
}

/* Loads a matrix to uniform with location in shader program */
void ShaderProgram::loadMatrix(int location, const glm::mat4 & matrix) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
