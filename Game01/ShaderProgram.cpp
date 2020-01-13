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
	locationLightPosition = getUniformLocation("light_position");
	locationLightColor = getUniformLocation("light_color");
}

void ShaderProgram::loadLight(const Light & light)
{
	this->loadVec3(this->locationLightPosition, light.getPosition());
	this->loadVec3(this->locationLightColor, light.getColor());
}
