#include <fstream>
#include <iostream>
#include "../src/Vehicle.hpp"

void test1() {
  Vehicle* v = new Vehicle("../res/models/stagecoach.obj", glm::vec3(0, 0, 0));

  v->move(10);

  // The normal way
  // assert(v->vehicleModel->position.z == 10.0f);


  // The i need to get a point with writing results to a file way
  bool isAtTen = v->vehicleModel->position.z == 10.0f;

  // Create stream and open file
  std::ofstream fs;
  fs.open("../test/results.txt");

  // Write the 'score' to the file
  if (isAtTen) {
    fs << "The test has been successfully completed";
  } else {
    fs << "The test failed";
    fs.close();
    assert(false);
  }

  // Close the file
  fs.close();
}