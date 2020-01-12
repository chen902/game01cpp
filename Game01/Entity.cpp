#include "Entity.h"


Entity::Entity(TexturedModel & model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) : 
	model(model), 
	position(position), 
	rotX(rotX), 
	rotY(rotY),
	rotZ(rotZ),
	scale(scale)
{

}

Entity::~Entity()
{
}
