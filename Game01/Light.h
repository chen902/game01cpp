#pragma once
#include <glm/vec3.hpp>

class Light
{
public:
	Light(const glm::vec3 position, const glm::vec3 color);
	~Light();

	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;

private:
	glm::vec3 position;
	glm::vec3 color;
};

