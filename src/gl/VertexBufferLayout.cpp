//
//  VertexBufferLayout.cpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

namespace rl {
    unsigned int LayoutElement::GetSizeOfType()
    {
        switch(type)
        {
            case GL_FLOAT:
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_BYTE:
                return sizeof(GLbyte);
        }
        ASSERT(false);
        return 0;
    }

    VertexBufferLayout::VertexBufferLayout()
    : m_Stride(0)
    {
        
    }

    VertexBufferLayout::VertexBufferLayout(const std::vector<LayoutElement>& layoutElements)
    {
        for (auto element : layoutElements)
        {
            m_Layouts.push_back(element);
            
            m_Stride += element.count * element.GetSizeOfType();
        }
    }

    VertexBufferLayout::~VertexBufferLayout()
    {
        // TODO: ... nothing maybe.
    }

    template<>
    void VertexBufferLayout::Add<float>(unsigned int cnt, unsigned char normalized)
    {
        LayoutElement elem = {GL_FLOAT, cnt, normalized};
        m_Layouts.push_back(elem);
        m_Stride += cnt * sizeof(GLfloat);
    }

    template<>
    void VertexBufferLayout::Add<unsigned int>(unsigned int cnt, unsigned char normalized)
    {
        LayoutElement elem = {GL_UNSIGNED_INT, cnt, normalized};
        m_Layouts.push_back(elem);
        m_Stride += cnt * sizeof(GLuint);
    }

    template<>
    void VertexBufferLayout::Add<char>(unsigned int cnt, unsigned char normalized)
    {
        LayoutElement elem = {GL_BYTE, cnt, normalized};
        m_Layouts.push_back(elem);
        m_Stride += cnt * sizeof(GLbyte);
    }
}
