#include "Light.h"



Light::Light(const glm::vec3 position, const glm::vec3 color) : position(position), color(color)
{
}


Light::~Light()
{
}

glm::vec3 Light::getPosition() const
{
	return this->position;
}

glm::vec3 Light::getColor() const
{
	return this->color;
}
