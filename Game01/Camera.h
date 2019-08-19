#pragma once
#include <glm/vec3.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, float pitch, float roll, float yaw) : 
		position(position), 
		pitch(pitch), 
		roll(roll), 
		yaw(yaw) 
	{};
	
	~Camera();
	glm::vec3 getPosition() const { return position; };
	float getPitch() const { return this->pitch; };
	float getRoll() const { return this->roll; };
	float getYaw() const { return this->yaw; };

private:
	glm::vec3 position;
	float pitch;
	float roll;
	float yaw;
};

