#pragma once
#include <glm/vec3.hpp>

class Camera
{
public:
	Camera(glm::vec3 position) : position(position) {};
	~Camera();
	glm::vec3 getPosition() const { return position; };

private:
	glm::vec3 position;
};

