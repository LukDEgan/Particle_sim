#include "util.h"
#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* fileName) {
  FILE* fp;
  long size = 0;
  char* content;
  fp = fopen(fileName, "rb");
  if (fp == NULL) {
    printf("Couldn't open file %s\n", fileName);
    exit(EXIT_FAILURE);
  }
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp) + 1;
  fclose(fp);

  fp = fopen(fileName, "r");
  content = malloc(size);
  fread(content, 1, size - 1, fp);
  content[size - 1] = '\0';
  fclose(fp);

  return content;
}