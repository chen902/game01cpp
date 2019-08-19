/*
	This class creats the bond between a 3d model and a position withing the game world.
*/
#pragma once
#include <glm/vec3.hpp>
#include "RawModel.h"

class Entity
{
public:
	Entity(RawModel& model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	~Entity();
	glm::vec3 getPosition() const { return position; };
	RawModel& getModel() const { return model; };
	float getRotX() const { return this->rotX; }
	float getRotY() const { return this->rotY; }
	float getRotZ() const { return this->rotZ; }
	void increasePosition(float x, float y, float z) { this->position.x += x; this->position.y += y, this->position.z += z; }
	void increaseRotation(float x, float y, float z) { this->rotX += x; this->rotY += y; this->rotZ += z; }
	float getScale() const { return this->scale; }


private:
	RawModel& model;
	glm::vec3 position;
	float rotX;
	float rotY;
	float rotZ;
	float scale;
};

