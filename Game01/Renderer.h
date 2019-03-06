#pragma once
#include "RawModel.h"
#include "ShaderProgram.h"

class Renderer
{
public:
	~Renderer();
	void prepare();
	void render(const RawModel& model, const ShaderProgram& shader);
};

