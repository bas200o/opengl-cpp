#pragma once
#include "ObjModel.hpp"
#include "drawable.hpp"

class Building : public Drawable
{
public:
	Building(const std::string& filename, glm::vec3 position);

	~Building(); // Destructor
	Building(const Building& other); // Copy constructor
	Building& operator=(const Building& other); // Copy assignment operator

	ObjModel* buildingModel;

	void draw();	
};