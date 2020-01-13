#include "Camera.h"


Camera::~Camera()
{
}

void Camera::increasePosX(float val)
{
	this->position.x += val;
}

void Camera::increasePosY(float val)
{
	this->position.y += val;
}

void Camera::increasePosZ(float val)
{
	this->position.z += val;
}

void Camera::increasePitch(float val)
{
	this->pitch += val;
}

void Camera::increaseRoll(float val)
{
	this->roll += val;
}

void Camera::increaseYaw(float val)
{
	this->yaw += val;
}
