#pragma once
#include "ObjModel.hpp"
#include "drawable.hpp"

class Road : public Drawable
{
public:
	Road(const std::string& filename, glm::vec3 pos); // Constructor

	~Road(); // Destructor
	Road(const Road& other); // Copy Constructor
	Road& operator=(const Road& other); // Copy assignment constructor

	void draw();

	ObjModel* roadModel;
};