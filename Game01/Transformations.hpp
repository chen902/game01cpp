#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"
#include "Camera.h"

class Transformations {
public:
	static glm::mat4 createModelMatrix(const Entity& entity) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, entity.getPosition());
		model = glm::rotate(model, glm::radians(entity.getRotX()),glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity.getRotY()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(entity.getRotZ()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(entity.getScale()));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		return model;
	}

	static glm::mat4 createViewMatrix(const Camera& camera) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::vec3 pos = camera.getPosition();
		view = glm::translate(view, glm::vec3(-pos.x, -pos.y, -pos.z));
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		return view;
	}
};