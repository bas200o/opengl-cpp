#include "Building.hpp"

// Constructor for the Building class
Building::Building(const std::string& filename, glm::vec3 pos) : buildingModel(new ObjModel(filename, pos))
{

}

// Destructor for the Building class
Building::~Building()
{
	delete buildingModel;
}

// Copy constructor for the Building class
Building::Building(const Building& other)
{
	buildingModel = other.buildingModel;
}

// Copy assignment operator for the building class
Building& Building::operator=(const Building& other)
{
	buildingModel = other.buildingModel;
	return *this;
}

// Method for drawing the object
void Building::draw()
{
	buildingModel->draw();
}