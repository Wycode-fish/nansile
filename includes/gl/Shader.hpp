//
//  Shader.hpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include "glm.hpp"

struct ShaderSources
{
    std::string vsString;
    std::string fsString;
};
class Shader
{
public:
    Shader(const std::string& vsPath, const std::string& fsPath);
    void Use();
    void Drop();
    void SetUniform4f(const char* varName, float v1, float v2, float v3, float v4);
    void SetUniform3f(const char* varName, float v1, float v2, float v3);
    void SetUniform2f(const char* varName, float v1, float v2);
    void SetUniform1f(const char* varName, float v1);
    void SetUniform1i(const char* varName, unsigned int v1);
    void SetUniformMat4f(const char* varName, glm::mat4 src);
    ~Shader();
private:
    void CompileShaders(const ShaderSources& ssrc);
    ShaderSources ParseShaders(const std::string& vsPath, const std::string& fsPath);
    int GetUniformLocation(const char* vname);
    void CreateShader(const char* src, unsigned int* shaderID, unsigned int type);
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, unsigned int> m_LocationCache;
};

#endif /* Shader_hpp */
