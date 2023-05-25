#pragma once
#include <glm/glm.hpp>
#include "Vehicle.hpp"

struct GLFWwindow;

class FpsCam
{
public:
	FpsCam(GLFWwindow*);
	glm::vec3 position = glm::vec3(0, 0, 0);

	glm::mat4 getMatrix();
	void update(GLFWwindow*, Vehicle*);
	glm::vec3 getPosition();
	bool inCar = false;
	void enterCar();
	void exitCar();

private:
	
	glm::vec2 rotation = glm::vec2(0, 0);
	void move(float angle, float fac);
	
};