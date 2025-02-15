#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_gen.h"
#include <stdbool.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
int main() {
  GLFWwindow* window;
  if (!glfwInit()) {
    printf("GLFW Initialization failed\n");
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(800, 600, "LearningOpenGL", NULL, NULL);
  if (window == NULL) {
    printf("Window creation failed\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    glfwTerminate();
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  unsigned int shader = buildShader(
      createShader("shaders/base_vertex.glsl", GL_VERTEX_SHADER),
      createShader("shaders/base_fragment.glsl", GL_FRAGMENT_SHADER));
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    processInput(window);
    glUseProgram(shader);
    glfwSwapBuffers(window);
  }
  glDeleteProgram(shader);
  glfwTerminate();

  return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}