//
//  VertexBufferLayout.hpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <stdio.h>
#include <vector>

struct LayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    unsigned int GetSizeOfType();
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    VertexBufferLayout(const std::vector<LayoutElement>& layoutElements);
    ~VertexBufferLayout();
    template<typename T>
    void Add(unsigned int cnt, unsigned char normalized)
    {
        //TODO: construct LayoutElement with input info;
    }
    inline std::vector<LayoutElement> GetLayouts() { return m_Layouts;}
    inline unsigned int GetStride() { return m_Stride;}
private:
    std::vector<LayoutElement> m_Layouts;
    unsigned int m_Stride;
};

#endif /* VertexBufferLayout_hpp */
