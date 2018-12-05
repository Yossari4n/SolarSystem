#ifndef Mesh_h
#define Mesh_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "ShaderProgram.h"

// TODO to new files
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int ID;
    std::string Type;
    std::string Path;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures);
    ~Mesh();
    
    void Draw(ShaderProgram shader);
    
//private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
    
    void SetupMesh();
};

#endif
