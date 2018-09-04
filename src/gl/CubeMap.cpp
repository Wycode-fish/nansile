//
//  CubeMap.cpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "CubeMap.hpp"
#include "Renderer.hpp"
#include "stb_image.hpp"
#include "TextEditor.hpp"

namespace rl {
    
    std::unordered_map<const char*, CubeMap*> CubeMap::CubeMapCache;

    CubeMap* CubeMap::GetCubeMap(std::vector<std::string>& filePaths)
    {
        if (filePaths.size() == 0 || strcmp(filePaths[0].c_str(), "") == 0)
        {
            return nullptr;
        }
        auto it = CubeMapCache.find(filePaths[0].c_str());
        if (it != CubeMapCache.end())
        {
            return CubeMapCache[filePaths[0].c_str()];
        }
        else
        {
            CubeMap* cubeMap = new CubeMap(filePaths);
            return cubeMap;
        }
        return nullptr;
    }

    CubeMap::CubeMap()
    : m_RendererID(0), m_LocalBuffer(NULL), m_Width(0), m_Height(0), m_BPP(0), m_Format(0)
    {
        // TODO: nothing. This default constructor is only exist for unordered_map initilization of Texture resources.
    }

    CubeMap::CubeMap(std::vector<std::string>& filePaths)
    : m_RendererID(0), m_LocalBuffer(NULL), m_FilePaths(filePaths), m_Width(0), m_Height(0), m_BPP(0), m_Format(0)
    {
        LoadCubeMapTexture(filePaths);
        if (CubeMapCache.find(filePaths[0].c_str()) == CubeMapCache.end())
            CubeMapCache[TextEditor::Str2ValuePtr(filePaths[0])] = this;
    }

    CubeMap::~CubeMap()
    {
        GLCALL(glDeleteTextures(1, &m_RendererID));
    }

    void CubeMap::Bind(unsigned int slot)
    {
    //    if (m_LocalBuffer==NULL)
    //        LoadTexture(m_FilePath);
    //    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
        GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
    }

    void CubeMap::Unbind()
    {
        GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
    }

    void CubeMap::LoadCubeMapTexture(std::vector<std::string>& filePaths)
    {
        m_FilePaths = filePaths;
        
        GLCALL(glGenTextures(1, &m_RendererID));
        GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
        
        for (int i=0; i<m_FilePaths.size(); i++)
        {
            stbi_set_flip_vertically_on_load(0);
            m_LocalBuffer = stbi_load(m_FilePaths[i].c_str(), &m_Width, &m_Height, &m_BPP, 4);
            m_Format = (m_BPP == 3)?GL_RGB8:GL_RGBA8;
            GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_Format, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_LocalBuffer));
            if (m_LocalBuffer)
                stbi_image_free(m_LocalBuffer);
        }
        
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    }
    
}
