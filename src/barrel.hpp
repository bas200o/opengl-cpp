#pragma once
#include "ObjModel.hpp"

class Barrel
{
public:
	Barrel(const std::string& original_filename, const std::string& trans_filename, glm::vec3 pos); // Constructor

	~Barrel(); // Destructor
	Barrel(const Barrel& other); // Copy constructor
	Barrel& operator=(const Barrel& other); // Copy assignment operator

	void draw();
	float breakBarrel(glm::vec3 camera_pos);
	void restoreBarrel();

	ObjModel* originalBarrelModel;
	ObjModel* transformedBarrelModel;
	ObjModel* BarrelToDisplay;
	bool broken;
};