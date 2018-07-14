//
//  Model.hpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"

struct ModelElement
{
    unsigned int m_Type;
    unsigned int m_VtxCnt;
    unsigned int m_ElemPerVer;
    unsigned int m_Tag;
    unsigned char m_Normalized;
    enum TAG
    {
        VBO, IBO
    };
    void* m_Data;
};

struct ModelElement_Group
{
    static std::unordered_map<const char*, ModelElement_Group> ModelElement_Group_Prefabs;
    
    void* m_VboData;
    unsigned int m_VboSize;
    VertexBufferLayout m_VboLayout;
    
    void* m_IboData;
    unsigned int m_IboCnt;
};

class Model
{
public:
    Model(const std::vector<VertexBuffer*> vbos, IndexBuffer* ibo);
    Model(const void* data, unsigned int size, VertexBufferLayout layout, IndexBuffer* ibo);
    ~Model();
    void Use();
    inline unsigned int GetCount() { return m_Ibo->GetCount(); }
private:
    VertexArray m_Vao;
    std::vector<VertexBuffer*> m_Vbos;
    
    VertexBuffer* m_Vbo;
    VertexBufferLayout m_Vbo_Layout;
    
    IndexBuffer* m_Ibo;
};

#endif /* Model_hpp */
