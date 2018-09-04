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
#include "ml.h"
#include "MetaData.hpp"

namespace rl {
    
    struct ShaderSources
    {
        std::string vsString;
        std::string fsString;
    };
    
    class Shader
    {
    public:
        static Shader* PlainShader;
        static Shader* DefaultShader;
        
    public:
        Shader(const std::string& vsPath, const std::string& fsPath);
        Shader(ShaderSources shaderSrc);
        ~Shader();
        
    public:
        void Use();
        void Drop();
        bool SetUniform4f(const char* varName, float v1, float v2, float v3, float v4);
        bool SetUniform3f(const char* varName, float v1, float v2, float v3);
        bool SetUniform2f(const char* varName, float v1, float v2);
        bool SetUniform1f(const char* varName, float v1);
        bool SetUniform1i(const char* varName, unsigned int v1);
        bool SetUniformMat4f(const char* varName, ml::Matrix4f src);
        bool SetUniformVec3f(const char* varName, ml::Vector3f src);

        
    private:
        void            CompileShaders(const ShaderSources& ssrc);
        ShaderSources   ParseShaders(const std::string& vsPath, const std::string& fsPath);
        int             GetUniformLocation(const char* vname);
        void            CreateShader(const char* src, unsigned int* shaderID, unsigned int type);
    private:
        unsigned int                                    m_RendererID;
        std::unordered_map<std::string, unsigned int>   m_LocationCache;
        
    public:
        DECLARE_META(Shader);
    };
        
}


#endif /* Shader_hpp */
