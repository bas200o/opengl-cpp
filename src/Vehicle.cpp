#include "Vehicle.hpp"

// Constructor for the vehicle class
Vehicle::Vehicle(const std::string& filename, glm::vec3 pos) : vehicleModel(new ObjModel(filename, pos))
{
}

// Destructor for the vehicle class
Vehicle::~Vehicle()
{
	delete vehicleModel;
}

// Copy constructor for the vehicle class
Vehicle::Vehicle(const Vehicle& other)
{
	vehicleModel = other.vehicleModel;
}

// Copy assignment operator
Vehicle& Vehicle::operator=(const Vehicle &other)
{
	vehicleModel = other.vehicleModel;
	return *this;
}

// Method which allows the vehicle to move along the z-axis
void Vehicle::move(float amount)
{
		vehicleModel->position.z += amount;
}

// Method which will draw the vehicle
void Vehicle::draw()
{
	vehicleModel->draw();
}