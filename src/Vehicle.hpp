#pragma once
#include "ObjModel.hpp"
#include "drawable.hpp"

class Vehicle : public Drawable
{
public:
	Vehicle(const std::string& filename, glm::vec3 pos); // Constructor

	~Vehicle(); // Destructor
	Vehicle(const Vehicle& other); // Copy constructor
	Vehicle& operator=(const Vehicle& other); // Copy assignment operator

	void draw();
	void move(float amount);
	void move();

	ObjModel* vehicleModel;
};