//
//  VertexBuffer.hpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <stdio.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, const unsigned int& size);
    VertexBuffer(const void* data, const unsigned int& m_Type, const unsigned int& m_ElemPerVtx, const unsigned int& m_VtxCnt, const unsigned char& m_Normalized);
    ~VertexBuffer();
    void Init(const void* data, const unsigned int& size);
    void Bind() const;
    void Unbind() const;
    unsigned int GetSizeOfType();
public:
    inline unsigned int GetElemPerVtx() { return m_ElemPerVtx; }
    inline unsigned int GetNormalized() { return m_Normalized; }
    inline unsigned int GetType() { return m_Type; }

private:
    unsigned int m_Type;
    unsigned int m_ElemPerVtx;
    unsigned int m_VtxCnt;
    unsigned char m_Normalized;
    unsigned int m_RendererID;
};

#endif /* VertexBuffer_hpp */
