/*
    Eindopdracht C++ & opengl

    @author Bas Winkelhof
    2120947
*/

// Includes and defines
#define STB_IMAGE_IMPLEMENTATION

#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <iomanip>
#include <iostream>
#include "Building.hpp"
#include "FpsCam.hpp"
#include "ObjModel.hpp"
#include "Road.hpp"
#include "Texture.hpp"
#include "Vehicle.hpp"
#include "barrel.hpp"
#include "drawable.hpp"
#include "tigl.hpp"
#include "../test/test.hpp"


using tigl::Vertex;

// Global objects
std::string scoreFile = "../res/score.txt";
float currentScore = 0.0;

GLFWwindow* window;

Vehicle* stagecoach;

// Vectors used for looping through the objects, and simplyfying the drawing of
// said objects
std::vector<Barrel*> barrels;
std::vector<Drawable*> drawables;

float globalY = -1.0f;

FpsCam* camera;
Texture* ground;

void init();
void update();
void draw();
void drawModels();
void initModels();
void readScore();
void writeScore();

float operator"" _m(long double x) {
  return x;
}

float operator"" _cm(long double x) {
  return x / 100;
}

int main(int argc, char *argv[]) {
  std::cout << argc << std::endl;
  if (argc > 1) {
    for (int i = 0; i < argc; ++i) {
      std::string str = argv[i];

      // Start unit tests
      if(str.compare("test")) {
        test1();
      }
    }
    return 0;
  }


  try {
    if (glfwInit()) {
      std::cout << "GLFW success" << std::endl;
    } else {
      throw "Could not initialize glwf program quits";
    }

    window = glfwCreateWindow(1400, 800, "opengl cpp", NULL, NULL);

    if (window) {
      std::cout << "success creating a window" << std::endl;
    } else {
      glfwTerminate();
      throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);
    std::cout << glGetString(GL_RENDERER) << "\n"
              << glGetString(GL_VERSION) << std::endl;
  } catch (std::string error) {
    std::cout << "ERROR: " << error << std::endl;
    return -1;
  }

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

  ground = new Texture("../res/models/sandy_ground.png");
  camera = new FpsCam(window);

  initModels();
}

void update() {
  // Update the camera
  camera->update(window, stagecoach);
  // Update the stagecoach
  if (!camera->inCar) {
    stagecoach->move();
  }

  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    // Check whether the player is close to a barrel
    glm::vec3 currentPos = camera->getPosition();
    for (std::vector<Barrel*>::iterator it = barrels.begin();
         it != barrels.end(); it++) {
      currentScore = currentScore + (*it)->breakBarrel(currentPos);
    }
  }

  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    if (camera->inCar)
      camera->exitCar();
    else if (!camera->inCar)
      camera->enterCar();
  }

  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    // Loop through all the Barrels, which will then get 'repaired'
    for (std::vector<Barrel*>::iterator it = barrels.begin();
         it != barrels.end(); it++) {
      (*it)->restoreBarrel();
    }
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

  drawModels();
}

/**
 * draws all models
 */
void drawModels() {
  // Draw all non ground models
  for (std::vector<Drawable*>::iterator it = drawables.begin();
       it != drawables.end(); it++) {
    (*it)->draw();
  }

  // Bind the sand texture
  ground->bind();

  // Draw the ground(sand) texture
  tigl::begin(GL_QUADS);
  tigl::addVertex(
      Vertex::PT(glm::vec3(-25, globalY - 0.1f, -25), glm::vec2(0, 0)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(25, globalY - 0.1f, -25), glm::vec2(0, 1)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(25, globalY - 0.1f, 25), glm::vec2(1, 1)));
  tigl::addVertex(
      Vertex::PT(glm::vec3(-25, globalY - 0.1f, 25), glm::vec2(1, 0)));
  tigl::end();
}

void initModels() {
  // Initialize all the buildings
  Building* church;
  Building* shed;
  Building* trading;
  Building* ammunition;
  Building* grand_hotel;

  stagecoach = new Vehicle("../res/models/stagecoach.obj",
                           glm::vec3(0, globalY + 30.0_cm, 0));
  drawables.push_back(stagecoach);

  // Load in Obj files for the Buildings
  church = new Building("../res/models/church.obj",
                        glm::vec3(0.0_m, globalY, -8.0_m));
  shed =
      new Building("../res/models/shed.obj", glm::vec3(-5.0_m, globalY, 6.0_m));
  trading = new Building("../res/models/bld_trading_post.obj",
                         glm::vec3(-3.0_m, globalY, 10.0_m));
  ammunition = new Building("../res/models/bld_ammunition.obj",
                            glm::vec3(-3.0_m, globalY, 0.0_m));
  grand_hotel = new Building("../res/models/bld_grand_hotel.obj",
                             glm::vec3(3.0_m, globalY, 6.0_m));

  // Add all the Buildings to their vector
  drawables.push_back(church);
  drawables.push_back(shed);
  drawables.push_back(trading);
  drawables.push_back(ammunition);
  drawables.push_back(grand_hotel);

  // Add barrles next to the road
  for (int i = 1; i < 6; i++) {
    Barrel* barrel = new Barrel("../res/models/barrel.obj",
                                "../res/models/broken_barrel.obj",
                                glm::vec3(2.3_m, globalY, i * 3.0_m));

    drawables.push_back(barrel);
    barrels.push_back(barrel);
  }

  for (int i = 0; i < 5; i++) {
    Road* road = new Road("../res/models/road_straight.obj",
                          glm::vec3(0.0_m, globalY, i * 5.0_m));
    drawables.push_back(road);
  }

  // set camera next to road as to not spawn inside the car
  camera->position.x = -3.0f;
}

void writeScore() {
  // Create stream and open file
  std::ofstream fs;
  fs.open(scoreFile);

  // Write the 'score' to the file
  fs << "Your Score is: " << (int)currentScore << '\n';

  // Close the file
  fs.close();
}

void readScore() {
  // Create stream and open file
  std::fstream fs;
  fs.open(scoreFile);

  std::cout << std::filesystem::current_path() << std::endl;
  // Print out the currently saved string in the file
  std::string read_string;
  while (fs >> read_string) {
    std::cout << read_string << " ";
  }

  std::cout << "" << std::endl;
  // Close the file
  fs.close();
}
