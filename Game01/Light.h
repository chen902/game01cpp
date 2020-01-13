#pragma once
#include <glm/vec3.hpp>

class Light
{
public:
	Light(const glm::vec3 position, const glm::vec3 color);
	~Light();

	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;

	void increasePosX(float val) { this->position.x += val; };
	void increasePosY(float val) { this->position.y += val; };
	void increasePosZ(float val) { this->position.z += val; };

private:
	glm::vec3 position;
	glm::vec3 color;
};

