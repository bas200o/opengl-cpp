#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "tigl.hpp"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();

static int CompileShader(const std::string& source, unsigned int type){
	unsigned int id  = glCreateShader(GL_VERTEX_SHADER);
}

static int CreateShader(const std::string& vertexShader,
                        const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	

}

int main(void) {
  if (!glfwInit())
    throw "Could not initialize glwf";

  std::cout << glewInit() << std::endl;

  window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    throw "Could not initialize glwf";
  }

  glfwMakeContextCurrent(window);

  std::cout << glewInit() << std::endl;

  std::cout << glGetString(GL_VERSION) << std::endl;

  init();

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  unsigned int buffer = 0;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 3,0 );

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

void init() {
  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, true);
  });
}
