//
//  VertexArray.cpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

void VertexArray::Init()
{
    GLCALL(glGenVertexArrays(1, &m_RendererID));
    GLCALL(glBindVertexArray(m_RendererID));
}

VertexArray::VertexArray()
: m_RendererID(0)
{
    Init();
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexArray::Bind(VertexBuffer& vbo, VertexBufferLayout& layout) const
{
    vbo.Bind();
    GLCALL(glBindVertexArray(m_RendererID));
    auto elements = layout.GetLayouts();
    unsigned int offset = 0;
    for (int i=0; i<elements.size(); i++)
    {
        auto elem = elements[i];
        GLCALL(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void*)offset));
        GLCALL(glEnableVertexAttribArray(i));
        offset += elem.count * elem.GetSizeOfType();
    }
    
}

void VertexArray::Bind(VertexBuffer& vpos, VertexBuffer& tcs) const
{
    GLCALL(glBindVertexArray(m_RendererID));
    vpos.Bind();
    GLCALL(glVertexAttribPointer(VTX_POS, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0));
    GLCALL(glEnableVertexAttribArray(VTX_POS));
    tcs.Bind();
    GLCALL(glVertexAttribPointer(VTX_TCOOR, 2, GL_FLOAT, GL_FALSE, 0, (const void*)0));
    GLCALL(glEnableVertexAttribArray(VTX_TCOOR));
}

void VertexArray::Bind(std::vector<VertexBuffer*> vbos) const
{
    GLCALL(glBindVertexArray(m_RendererID));
    for (int i=0; i<vbos.size(); i++)
    {
        vbos[i]->Bind();
        GLCALL(glVertexAttribPointer(i, vbos[i]->GetElemPerVtx(), vbos[i]->GetType(), vbos[i]->GetNormalized(), 0, (const void*)0));
        GLCALL(glEnableVertexAttribArray(i));
    }
    
}

void VertexArray::Unbind(VertexBuffer& vbo) const
{
    GLCALL(vbo.Unbind());
    GLCALL(glBindVertexArray(0));
}

void VertexArray::Unbind() const
{
    GLCALL(glBindVertexArray(0));
}

