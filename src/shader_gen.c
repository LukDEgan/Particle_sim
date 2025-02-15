#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_gen.h"
#include <stdio.h>
#include "util.h"
unsigned int createShader(const char* shaderFile, unsigned int shaderType) {
  GLint success = 0;
  GLint logSize = 0;

  unsigned int shader = glCreateShader(shaderType);

  const char* shaderContent = readFile(shaderFile);
  glShaderSource(shader, 1, &shaderContent, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    GLchar infoLog[logSize];
    glGetShaderInfoLog(shader, logSize, &logSize, infoLog);
    glDeleteShader(shader);
    printf("Shader Error: %s\n", infoLog);
  }
  return shader;
}
unsigned int buildShader(unsigned int vertexShader, unsigned int fragShader) {
  GLint success = 0;
  GLint logSize = 0;
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &logSize);
    GLchar infoLog[logSize];
    glGetShaderInfoLog(shaderProgram, logSize, &logSize, infoLog);
    glDeleteShader(shaderProgram);
    printf("Linking Error: %s\n", infoLog);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);
  return shaderProgram;
}