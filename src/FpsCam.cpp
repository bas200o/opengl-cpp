#include "FpsCam.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Vehicle.hpp"

FpsCam::FpsCam(GLFWwindow* window) {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::mat4 FpsCam::getMatrix() {
  glm::mat4 ret(1.0f);
  ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
  ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
  ret = glm::translate(ret, position);
  return ret;
}

void FpsCam::move(float angle, float fac) {
  position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
  position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}

void FpsCam::enterCar() {
  inCar = true;
}

void FpsCam::exitCar() {
  inCar = false;
}

void FpsCam::update(GLFWwindow* window, Vehicle* car) {
  double x, y;
  glfwGetCursorPos(window, &x, &y);

  static double lastX = x;
  static double lastY = y;

  rotation.x -= (float)(lastY - y) / 100.0f;
  rotation.y -= (float)(lastX - x) / 100.0f;

  lastX = x;
  lastY = y;

  if (!inCar) {
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      move(0, 0.05f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      move(180, 0.05f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      move(90, 0.05f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      move(-90, 0.05f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      position.y = -1.0f;

    if (position.y < 0.0f) {
      position.y += 0.05f;
    }

  } else {
    position.x = -car->vehicleModel->position.x;
    position.y = -0.5 + car->vehicleModel->position.y;
    position.z = -1.0 - car->vehicleModel->position.z;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      car->move(0.1f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      car->move(-.1f);
  }
}

glm::vec3 FpsCam::getPosition() {
  return position;
}