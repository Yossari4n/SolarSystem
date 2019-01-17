#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class ShaderProgram {
public:
    enum TYPE {
        COLOR_PURE = 0,
        COLOR_LIGHT_RECEIVER,
        TEXTURE_PURE,
        TEXTURE_LIGHT_RECEIVER,
        
        COUNT
    };
    
    ShaderProgram();
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ~ShaderProgram();
    
    void AttachShaders(const char *vertex_path, const char *fragment_path, const char *geometry_path = nullptr);
    void Use() const;
    
    int ID() const;
    
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, const glm::vec2 &vec) const;
    void SetVec2(const std::string &name, float x, float y) const;
    void SetVec3(const std::string &name, const glm::vec3 &vec) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetVec4(const std::string &name, const glm::vec4 &vec) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
    
private:
    unsigned int m_ID;
    
    void LinkProgram();
    unsigned int AttachShader(const char *path, GLenum shader);
};

#endif
