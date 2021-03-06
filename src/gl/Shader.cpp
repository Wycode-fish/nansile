//
//  Shader.cpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Shader.hpp"
#include "Renderer.hpp"
#include "FileReader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace rl {
    
    DEFINE_META(rl::Shader)
    {
        ADD_MEMBER(m_RendererID);
        ADD_MEMBER(m_LocationCache);
    }

    Shader* Shader::PlainShader = nullptr;
    Shader* Shader::DefaultShader = nullptr;
    
    Shader::Shader(const std::string& vsPath, const std::string& fsPath)
    {
        GLCALL(m_RendererID =glCreateProgram());
        CompileShaders(ParseShaders(vsPath, fsPath));
    }

    Shader::Shader(ShaderSources shaderSrc)
    {
        GLCALL(m_RendererID =glCreateProgram());
        CompileShaders(ParseShaders(shaderSrc.vsString, shaderSrc.fsString));
    }

    Shader::~Shader()
    {
        GLCALL(glDeleteProgram(m_RendererID));
    }


    void Shader::CreateShader(const char* src, unsigned int* id, unsigned int type)
    {
        GLCALL(*id = glCreateShader(type));
        GLCALL(glShaderSource(*id, 1, &src, NULL));
        GLCALL(glCompileShader(*id));
        GLint compileStatus;
        glGetShaderiv(*id, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE)
        {
            GLsizei logLength = 0;
            char info[1024];
            glGetShaderInfoLog(*id, 1024, &logLength, info);
            info[logLength] = '\0';
            std::cout<<"[OpenGL]: Shader Compile Failed. Info - "<<info<<std::endl;
        }
    }

    void Shader::CompileShaders(const ShaderSources& ssrc)
    {
        const char* vsSrc = ssrc.vsString.c_str();
        unsigned int vs;
        CreateShader(vsSrc, &vs, GL_VERTEX_SHADER);
        
        const char* fsSrc = ssrc.fsString.c_str();
        unsigned int fs;
        CreateShader(fsSrc, &fs, GL_FRAGMENT_SHADER);
        
        GLCALL(glAttachShader(m_RendererID, vs));
        GLCALL(glAttachShader(m_RendererID, fs));
        GLCALL(glLinkProgram(m_RendererID));
        
        GLCALL(glDeleteShader(vs));
        GLCALL(glDeleteShader(fs));
    }


    ShaderSources Shader::ParseShaders(const std::string& vsPath, const std::string& fsPath)
    {
        return {FileReader::ReadFile(vsPath), FileReader::ReadFile(fsPath)};
    }


    void Shader::Use()
    {
        GLCALL(glUseProgram(m_RendererID));
    }

    void Shader::Drop()
    {
        GLCALL(glUseProgram(0));
    }


    int Shader::GetUniformLocation(const char* varName)
    {
        if (m_LocationCache.find(varName) != m_LocationCache.end())
            return m_LocationCache[varName];
        
        GLCALL(int location = glGetUniformLocation(m_RendererID, varName));
        if (location == -1)
            std::cout<<"[OpenGL]: Uniform location can't be reached. Because variable '"<<varName<<"'doesn't exist."<<std::endl;
        m_LocationCache[varName] = location;
        return location;
    }

    bool Shader::SetUniform4f(const char* varName, float v1, float v2, float v3, float v4)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform4f(location, v1, v2, v3, v4));
        return true;
    }

    bool Shader::SetUniform2f(const char* varName, float v1, float v2)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform2f(location, v1, v2));
        return true;
    }

    bool Shader::SetUniform3f(const char* varName, float v1, float v2, float v3)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform3f(location, v1, v2, v3));
        return true;
    }

    bool Shader::SetUniform1f(const char* varName, float v1)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform1f(location, v1));
        return true;
    }

    bool Shader::SetUniform1i(const char* varName, unsigned int v1)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform1i(location, v1));
        return true;
    }


    bool Shader::SetUniformMat4f(const char* varName, ml::Matrix4f src)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, &src[0][0]));
        return true;
    }
    
    bool Shader::SetUniformVec3f(const char* varName, ml::Vector3f src)
    {
        GLCALL(int location = GetUniformLocation(varName));
        if (location == -1)
        {
            std::cout<<"[OpenGL]: Failed to set uniform variable'"<<varName<<"'."<<std::endl;
            return false;
        }
        GLCALL(glUniform3fv(location, 1, ml::ValuePtr(src)));
        return true;
    }
}
