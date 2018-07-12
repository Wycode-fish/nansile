//
//  CubeMap.hpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef CubeMap_hpp
#define CubeMap_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "Texture.hpp"

class CubeMap: public Texture
{
public:
    static std::unordered_map<const char*, CubeMap*> CubeMapCache;
    CubeMap(std::vector<std::string>& filePaths);
    CubeMap();
    ~CubeMap();
    void Bind(unsigned int slot=0);
    void Unbind();
    void LoadCubeMapTexture(std::vector<std::string>& filePaths);
    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }
    inline std::vector<std::string> GetFilePaths() { return m_FilePaths; }
private:
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    std::vector<std::string> m_FilePaths;             // ORDER MATTERS HERE!: POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z;
    unsigned int m_Format;
    int m_Width;
    int m_Height;
    int m_BPP;
};

#endif /* CubeMap_hpp */
