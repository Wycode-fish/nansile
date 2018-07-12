//
//  VertexBuffer.cpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include <iostream>

unsigned int VertexBuffer::GetSizeOfType()
{
    switch(m_Type)
    {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_BYTE:
            return 1;
    }
    ASSERT(false);
    return 0;
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size)
: m_RendererID(0)
{
    Init(data, size);
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int& type, const unsigned int& epv, const unsigned int& vc, const unsigned char& norm)
: m_RendererID(0), m_Type(type), m_ElemPerVtx(epv), m_VtxCnt(vc), m_Normalized(norm)
{
    Init(data, GetSizeOfType() * m_ElemPerVtx * m_VtxCnt);
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
//    std::cout<<"[OpenGL]: vbo destructor called. "<<"id: "<<m_RendererID<<std::endl;
}

void VertexBuffer::Init(const void* data, const unsigned int& size)
{
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    GLCALL(Unbind());
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
