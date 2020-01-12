#pragma once
#include "ModelTexture.h"
#include "RawModel.h"

class TexturedModel
{
public:
	TexturedModel(ModelTexture& texture, RawModel& model);
	~TexturedModel();
	RawModel& getModel() { return model; };
	ModelTexture& getTexture() { return texture; };

private:
	ModelTexture& texture;
	RawModel& model;
};

