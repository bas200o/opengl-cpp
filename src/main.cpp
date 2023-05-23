/*
    Eindopdracht C++ & opengl

    @author Bas Winkelhof
    2120947
*/

// Includes and defines
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Building.hpp"
#include "FpsCam.hpp"
#include "ObjModel.hpp"
#include "barrel.hpp"
#include "Road.hpp"
#include "Texture.hpp"
#include "Vehicle.hpp"
#include "tigl.hpp"

using tigl::Vertex;

// Global objects
std::string scoreFile = "../res/score.txt";
float currentScore = 0.0;

GLFWwindow* window;

ObjModel* skydome;
ObjModel* piano;
Vehicle* veh_stagecoach;

// Vectors used for looping through the objects, and simplyfying the drawing of
// said objects
std::vector<Building*> buildings;
std::vector<Barrel*> barrels;
std::vector<Road*> roads;

float global_y = -1.0f;

FpsCam* camera;
Texture* sand_ground;

void init();
void update();
void draw();
void draw_models();
void init_models();
void readScore();
void writeScore();

int main(void) {
  if (!glfwInit())
    throw "Could not initialize glwf";
  window = glfwCreateWindow(1400, 800, "opengl cpp", NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw "Could not initialize glwf";
  }
  glfwMakeContextCurrent(window);

  std::cout << glGetString(GL_RENDERER) << "\n" << glGetString(GL_VERSION) << std::endl;

  tigl::init();

  init();

  while (!glfwWindowShouldClose(window)) {
    update();
    draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

void init() {
  // Read the text file for the old scores
  readScore();

  tigl::shader->enableTexture(true);
  tigl::shader->enableColor(true);

  tigl::shader->enableLighting(true);
  tigl::shader->setLightCount(2);
  tigl::shader->setLightDirectional(0, false);
  tigl::shader->setLightDirectional(1, false);
  tigl::shader->setLightDirectional(2, true);
  tigl::shader->setLightPosition(0, glm::vec3(0, 100, 0));
  tigl::shader->setLightPosition(1, glm::vec3(0, 100, 0));
  tigl::shader->setLightPosition(2, glm::vec3(0, 100, 0));
  tigl::shader->setLightDiffuse(0, glm::vec3(1.0f, 0.5f, 0.31f));
  tigl::shader->setLightAmbient(1, glm::vec3(1.0f, 0.5f, 0.31f));
  tigl::shader->setShinyness(0.0001f);

  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, true);

      // Score is written to file on exit
      writeScore();
    }
  });

  sand_ground = new Texture("../models/sandy_ground.png");
  camera = new FpsCam(window);

  init_models();
}

void update() {
  // Update the camera
  camera->update(window);
  // Update the stagecoach
  veh_stagecoach->move();

  if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)) {
    // Check whether the player is close to a barrel
    glm::vec3 currentPos = camera->getPosition();
    for (std::vector<Barrel*>::iterator it = barrels.begin(); it != barrels.end(); it++) {
      currentScore = currentScore + (*it)->breakBarrel(currentPos);
    }

    // Check whether the player is close to the piano
    int x_dif = piano->position.x + currentPos.x;
    int y_dif = piano->position.z + currentPos.z;

    if (x_dif < 2.1 && x_dif > -1.1 && y_dif < 1.1 && y_dif > -1.1) {
      // Play the music
      // BASS_ChannelPlay(backgroundMusic, TRUE);
    }
  }

  if ((glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)) {
    // Loop through all the Barrels, which will then get 'repaired'
    for (std::vector<Barrel*>::iterator it = barrels.begin();
         it != barrels.end(); it++) {
      (*it)->restoreBarrel();
    }
  }

  if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)) {
    // Pause the music
    //_ChannelPause(backgroundMusic);
  }
}

void draw() {
  glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int width, height;
  glfwGetWindowSize(window, &width, &height);

  glViewport(0, 0, width, height);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          width / (float)height, 0.01f, 100.0f);

  tigl::shader->setProjectionMatrix(projection);
  tigl::shader->setViewMatrix(camera->getMatrix());
  tigl::shader->setModelMatrix(glm::mat4(1.0f));

  glEnable(GL_DEPTH_TEST);

  draw_models();
}

void draw_models() {
  // Draw the skydome
  skydome->draw();

  // Draw the piano
  piano->draw();

  // Draw all the current roads
  for (std::vector<Road*>::iterator it = roads.begin(); it != roads.end();
       it++) {
    (*it)->draw();
  }

  // Draw the vehicle
  veh_stagecoach->draw();

  // Draw all the current Barrels
  for (std::vector<Barrel*>::iterator it = barrels.begin(); it != barrels.end();
       it++) {
    (*it)->draw();
  }

  // Draw all the current buildings
  for (std::vector<Building*>::iterator it = buildings.begin();
       it != buildings.end(); it++) {
    (*it)->draw();
  }

  // Bind the sand texture
  sand_ground->bind();

  // Draw the ground(sand) texture
  tigl::begin(GL_QUADS);
  tigl::addVertex(
      Vertex::PT(glm::vec3(-25, global_y - 0.1f, -25), glm::vec2(0, 0)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(25, global_y - 0.1f, -25), glm::vec2(0, 1)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(25, global_y - 0.1f, 25), glm::vec2(1, 1)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(-25, global_y - 0.1f, 25), glm::vec2(1, 0)));
  tigl::end();
}

void init_models() {
  // Initialize all the Barrels
  Barrel* barrel1;
  Barrel* barrel2;
  Barrel* barrel3;
  Barrel* barrel4;
  Barrel* barrel5;

  // Initialize all the buildings
  Building* bld_church;
  Building* bld_shed;
  Building* bld_trading;
  Building* bld_ammunition;
  Building* bld_grand_hotel;

  // Initialize all the roads
  Road* road_straight_a;
  Road* road_straight_b;
  Road* road_straight_c;
  Road* road_straight_d;
  Road* road_lr_a;
  Road* road_lr_b;

  // Load in Obj files for the 'special' objects
  skydome =
      new ObjModel("../models/skydome.obj", glm::vec3(0, global_y, 0));
  piano =
      new ObjModel("../models/piano.obj", glm::vec3(10, global_y, 0));
  veh_stagecoach = new Vehicle("../models/stagecoach.obj",
                               glm::vec3(0, global_y + 0.3f, 0));

  // Load in Obj files for the Barrels
  barrel1 = new Barrel("../models/barrel.obj",
                           "../models/broken_barrel.obj",
                           glm::vec3(2.3f, global_y, 3));
  barrel2 = new Barrel("../models/barrel.obj",
                           "../models/broken_barrel.obj",
                           glm::vec3(2.3f, global_y, 6));
  barrel3 = new Barrel("../models/barrel.obj",
                           "../models/broken_barrel.obj",
                           glm::vec3(2.3f, global_y, 9));
  barrel4 = new Barrel("../models/barrel.obj",
                           "../models/broken_barrel.obj",
                           glm::vec3(2.3f, global_y, 12));
  barrel5 = new Barrel("../models/barrel.obj",
                           "../models/broken_barrel.obj",
                           glm::vec3(2.3f, global_y, 15));

  // Add all the Barrels to their vector
  barrels.push_back(barrel1);
  barrels.push_back(barrel2);
  barrels.push_back(barrel3);
  barrels.push_back(barrel4);
  barrels.push_back(barrel5);

  // Load in Obj files for the Buildings
  bld_church =
      new Building("../models/church.obj", glm::vec3(0, global_y, -8));
  bld_shed =
      new Building("../models/shed.obj", glm::vec3(-4, global_y, 6));
  bld_trading = new Building("../models/bld_trading_post.obj",
                             glm::vec3(-2, global_y, 10));
  bld_ammunition = new Building("../models/bld_ammunition.obj",
                                glm::vec3(-2, global_y, 16));
  bld_grand_hotel = new Building("../models/bld_grand_hotel.obj",
                                 glm::vec3(3, global_y, 6));

  // Add all the Buildings to their vector
  buildings.push_back(bld_church);
  buildings.push_back(bld_shed);
  buildings.push_back(bld_trading);
  buildings.push_back(bld_ammunition);
  buildings.push_back(bld_grand_hotel);

  // Load in Obj files for the Roads
  road_straight_a = new Road("../models/road_straight.obj",
                             glm::vec3(0, global_y, 0));
  road_straight_b = new Road("../models/road_straight.obj",
                             glm::vec3(0, global_y, 5));
  road_straight_c = new Road("../models/road_straight.obj",
                             glm::vec3(0, global_y, 10));
  road_straight_d = new Road("../models/road_straight.obj",
                             glm::vec3(0, global_y, 16));
  road_lr_a =
      new Road("../models/road_lr.obj", glm::vec3(-2, global_y, 0));
  road_lr_b =
      new Road("../models/road_lr.obj", glm::vec3(2, global_y, 0));

  // Add all the Roads to their vector
  roads.push_back(road_straight_a);
  roads.push_back(road_straight_b);
  roads.push_back(road_straight_c);
  roads.push_back(road_straight_d);
  roads.push_back(road_lr_a);
  roads.push_back(road_lr_b);
}

void writeScore() {
  // Create stream and open file
  std::ofstream myfile;
  myfile.open(barrel_file);

  // Write the 'score' to the file
  myfile << "Your Score is: " << currentScore
         << '\n';

  // Close the file
  myfile.close();
}

void readScore() {
  // Create stream and open file
  std::fstream stream;
  stream.open(scoreFile);

  // Print out the currently saved string in the file
  std::string read_string;
  while (myfile >> read_string) {
    std::cout << read_string << "\n";
  }

  // Close the file
  myfile.close();
}