#include "barrel.hpp"
#include <iostream>
#include <cmath>

// Constructor for the Barrel class
Barrel::Barrel(const std::string& original_filename, const std::string& trans_filename, glm::vec3 pos)
	: originalBarrelModel(new ObjModel(original_filename, pos)),
	transformedBarrelModel(new ObjModel(trans_filename, pos)),
	barrelToDisplay(new ObjModel(original_filename, pos)),
	broken(false)
{

}

// Destructor for the Barrel class
Barrel::~Barrel()
{
	delete originalBarrelModel;
	delete transformedBarrelModel;
	delete barrelToDisplay;
}

// Copy constructor for the Barrel class
Barrel::Barrel(const Barrel& other)
{
	originalBarrelModel = other.originalBarrelModel;
	transformedBarrelModel = other.transformedBarrelModel;
	barrelToDisplay = other.barrelToDisplay;
}

// Copy assignment operator for the Barrel class
Barrel& Barrel::operator=(const Barrel& other)
{
	originalBarrelModel = other.originalBarrelModel;
	transformedBarrelModel = other.transformedBarrelModel;
	barrelToDisplay = other.barrelToDisplay;

	return *this;
}

// Draw method for the Barrel class
void Barrel::draw()
{	
	barrelToDisplay->draw();
}

/**
 * This function replaces the barrel with a broken one and returns a score.
 * 
 * @return Score of the broken barrel
*/
float Barrel::breakBarrel(glm::vec3 cameraPos)
{
	if (!broken)
	{
		float x_dif = barrelToDisplay->position.x + cameraPos.x;
		float y_dif = barrelToDisplay->position.z + cameraPos.z;

		if (x_dif < 2.1 && x_dif > -1.1 && y_dif < 1.1 && y_dif > -1.1)
		{
			barrelToDisplay = transformedBarrelModel;
			broken = true;
			float score = 5.0 - (pow(x_dif, 2) + pow(y_dif, 2) *2 );
			std::cout << score << std::endl; 
			return score;
		}
	}
	return 0.0f;
}

void Barrel::restoreBarrel()
{
	barrelToDisplay = originalBarrelModel;
	broken = false;
}