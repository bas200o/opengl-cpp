#include "Road.hpp"

// Constructor for the Road class
Road::Road(const std::string& filename, glm::vec3 pos)
    : roadModel(new ObjModel(filename, pos)) {}

// Destructor for the Road class
Road::~Road() {
  delete roadModel;
}

// Copy Constructor for the Road class
Road::Road(const Road& other) {
  roadModel = other.roadModel;
}

// Copy assignment operator for the Road class
Road& Road::operator=(const Road& other) {
  roadModel = other.roadModel;
  return *this;
}

// Draw method for the Road class
void Road::draw() {
  roadModel->draw();
}