//
//  Texture.hpp
//  bird
//
//  Created by 汪依尘 on 6/12/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <unordered_map>
#include <utility>
#include <vector>

class Texture
{
public:
    static Texture* GetTexture(const char* filePath);
    Texture(const char* filePath);
    Texture();
    virtual ~Texture();
    virtual void Bind(unsigned int slot=0);
    virtual void Unbind();
    void LoadTexture(const char* filePath);
    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }
    inline const char* GetFilePath() { return m_FilePath; }
private:
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    const char* m_FilePath;
    unsigned int m_Format;
    int m_Width;
    int m_Height;
    int m_BPP;
};
#endif /* Texture_hpp */
