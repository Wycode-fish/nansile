//
//  Texture.cpp
//  bird
//
//  Created by 汪依尘 on 6/12/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Texture.hpp"
#include "Renderer.hpp"
#include <iostream>
#include "stb_image.hpp"
#include "ResourceManager.hpp"

namespace rl {
    
    std::string Texture::TypeNames[9] = {   "None", "Diffuse", "Specular",
                                            "Ambient", "Emissive", "Height",
                                            "Normal", "Shiness", "Opacity"
    };

    
    Texture* Texture::GetTexture(const char* filePath, unsigned char type)
    {
        if (filePath == nullptr || strcmp(filePath, "") == 0)
            return nullptr;
        
        auto it = ResourceManager::GetTextureResourceMap().find(filePath);
        if (it != ResourceManager::GetTextureResourceMap().end())
        {
            return ResourceManager::GetTextureResourceMap()[filePath];
        }
        else
        {
            Texture* texture = new Texture(filePath, type);
            return texture;
        }
        return nullptr;
    }

    Texture::Texture()
    : m_RendererID(0), m_FilePath(""), m_Type(TEXTYPE_NONE)
    {
        // TODO: nothing. This default constructor is only exist for unordered_map initilization of Texture resources.
        std::cout<<"[WARN]: Un-named texture genrerated."<<std::endl;
    }

//    Texture::Texture(const char* filePath)
//    : m_RendererID(0), m_FilePath(filePath), m_Type(TEXTYPE_NORMAL)
//    {
//        LoadTexture(filePath);
//        std::cout<<"[INFO]: '"<<filePath<<"' texture genrerated."<<std::endl;
//    }
    
    Texture::Texture(const char* filePath, unsigned char type)
    : m_RendererID(0), m_FilePath(filePath), m_Type(type)
    {
        LoadTexture(filePath);
        std::cout<<"[INFO]: '"<<filePath<<"' texture genrerated."<<std::endl;
    }

    Texture::~Texture()
    {
        if (m_FilePath != nullptr)
            delete m_FilePath;
        GLCALL(glDeleteTextures(1, &m_RendererID));
    }

    void Texture::Bind(unsigned int slot) const
    {
    //    if (m_LocalBuffer==NULL)
    //        LoadTexture(m_FilePath);
        GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
        GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }

    void Texture::Unbind() const
    {
        GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Texture::LoadTexture(const char* filePath)
    {
        m_FilePath = filePath;
        stbi_set_flip_vertically_on_load(1);
        int m_Width, m_Height, m_BPP;
        unsigned char* m_LocalBuffer = stbi_load(m_FilePath, &m_Width, &m_Height, &m_BPP, 4);
        unsigned m_Format = (m_BPP == 3)?GL_RGB8:GL_RGBA8;
        
        GLCALL(glGenTextures(1, &m_RendererID));
        GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
        
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_LocalBuffer));
        
        if (m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }
        
}

