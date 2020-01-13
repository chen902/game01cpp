#include "Camera.h"


Camera::~Camera()
{
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
