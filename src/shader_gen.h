#ifndef __SHADER_GEN_H__
#define __SHADER_GEN_H__

unsigned int createShader(const char* shaderFile, unsigned int shaderType);
unsigned int buildShader(unsigned int vertexShader, unsigned int fragShader);
#endif
