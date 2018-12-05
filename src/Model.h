#ifndef Model_h
#define Model_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "ShaderProgram.h"
#include "Mesh.h"

class Model {
public:
    Model(char *path);
    ~Model();
    
    void Draw(ShaderProgram shader);
    
//private:
    std::vector<Mesh> m_Meshes;
    std::vector<Texture> m_TexturesLoaded;
    std::string m_Directory;
    
    void LoadModel(std::string path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif
