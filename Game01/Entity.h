/*
	This class creats the bond between a 3d model and a position withing the game world.
*/
#pragma once
#include <glm/vec3.hpp>
#include "RawModel.h"

class Entity
{
public:
	Entity(RawModel& model, glm::vec3 position);
	~Entity();
	glm::vec3 getPosition() const { return position; };
	RawModel& getModel() const { return model; };


private:
	RawModel& model;
	glm::vec3 position;
};

