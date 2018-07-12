//
//  VertexArray.hpp
//  bird
//
//  Created by 汪依尘 on 6/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include <vector>

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
    enum VERTEX_ATTRIB
    {
        VTX_POS, VTX_TCOOR
    };
    VertexArray();
    ~VertexArray();
    void Bind(VertexBuffer& vbo, VertexBufferLayout& layout) const;
    void Bind(VertexBuffer& vpos, VertexBuffer& tcs) const;
    void Bind(std::vector<VertexBuffer*> vbos) const;
    void Unbind(VertexBuffer& vbo) const;
    void Unbind() const;
private:
    void Init();
private:
    unsigned int m_RendererID;
};
#endif /* VertexArray_hpp */
