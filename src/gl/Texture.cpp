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

Texture* Texture::GetTexture(const char* filePath)
{
    auto it = ResourceManager::GetTextureResourceMap().find(filePath);
    if (it != ResourceManager::GetTextureResourceMap().end())
    {
        return ResourceManager::GetTextureResourceMap()[filePath];
    }
    else
    {
        Texture* texture = new Texture(filePath);
//        ResourceManager::GetTextureResourceMap().insert(std::make_pair(filePath, texture));
        return texture;
    }
    return NULL;
}

Texture::Texture()
: m_RendererID(0), m_LocalBuffer(NULL), m_FilePath(""), m_Width(0), m_Height(0), m_BPP(0), m_Format(0)
{
    // TODO: nothing. This default constructor is only exist for unordered_map initilization of Texture resources.
    std::cout<<"[WARN]: Un-named texture genrerated."<<std::endl;
}

Texture::Texture(const char* filePath)
: m_RendererID(0), m_LocalBuffer(NULL), m_FilePath(filePath), m_Width(0), m_Height(0), m_BPP(0), m_Format(0)
{
    LoadTexture(filePath);
    std::cout<<"[INFO]: '"<<filePath<<"' texture genrerated."<<std::endl;

}

Texture::~Texture()
{
    GLCALL(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot)
{
//    if (m_LocalBuffer==NULL)
//        LoadTexture(m_FilePath);
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::LoadTexture(const char* filePath)
{
    m_FilePath = filePath;
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath, &m_Width, &m_Height, &m_BPP, 4);
    m_Format = (m_BPP == 3)?GL_RGB8:GL_RGBA8;
    
    GLCALL(glGenTextures(1, &m_RendererID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_LocalBuffer));
    
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

