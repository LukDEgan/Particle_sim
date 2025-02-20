#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <headers/shader.h>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "tiny_obj_loader.h"

using namespace std;
#define TINYOBJLOADER_IMPLEMENTATION
#define MAX_BONE_INFLUENCE 4

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  string type;
  string path;
};

class Mesh {
 public:
  // mesh Data
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;
  unsigned int VAO;

  // constructor
  Mesh(const char *path) {
    loadMesh(path);
    setupMesh();
  }

  // render the mesh
  void Draw(Shader &shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()),
                   GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

 private:
  // render data
  unsigned int VBO, EBO;

  void loadMesh(const char *path) {
    // Using TinyObjLoader to load the OBJ file
    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;
    string warning, err;

    // Load the model
    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

    if (!success) {
      printf("Error loading OBJ file: %s\n", err.c_str());
      return;
    }

    // Process the loaded data into vertices and indices
    for (const auto &shape : shapes) {
      for (size_t i = 0; i < shape.mesh.indices.size(); ++i) {
        tinyobj::index_t index = shape.mesh.indices[i];
        Vertex vertex;

        // Positions
        vertex.Position.x = attrib.vertices[3 * index.vertex_index + 0];
        vertex.Position.y = attrib.vertices[3 * index.vertex_index + 1];
        vertex.Position.z = attrib.vertices[3 * index.vertex_index + 2];

        // Normals (if available)
        if (!attrib.normals.empty()) {
          vertex.Normal.x = attrib.normals[3 * index.normal_index + 0];
          vertex.Normal.y = attrib.normals[3 * index.normal_index + 1];
          vertex.Normal.z = attrib.normals[3 * index.normal_index + 2];
        }

        // Texture coordinates (if available)
        if (!attrib.texcoords.empty()) {
          vertex.TexCoords.x = attrib.texcoords[2 * index.texcoord_index + 0];
          vertex.TexCoords.y = attrib.texcoords[2 * index.texcoord_index + 1];
        }

        // Store the vertex data
        vertices.push_back(vertex);
        indices.push_back(static_cast<unsigned int>(i));
      }
    }
  }

  // initializes all the buffer objects/arrays
  void setupMesh() {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, TexCoords));
    glBindVertexArray(0);
  }
};

#endif
