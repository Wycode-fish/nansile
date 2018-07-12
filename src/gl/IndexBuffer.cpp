//
//  IndexBuffer.cpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "IndexBuffer.hpp"

#include "Renderer.hpp"


IndexBuffer::IndexBuffer(const unsigned int* data, const int& cnt)
: m_RendererID(0), m_Count(cnt)
{
    Init(data, cnt);
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Init(const unsigned int* data, const int& cnt)
{
    GLCALL(glGenBuffers(1, &m_RendererID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * cnt, data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
