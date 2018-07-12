//
//  Model.cpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Model.hpp"

Model::Model(const std::vector<VertexBuffer*> vbos, IndexBuffer* ibo)
: m_Vbos(vbos), m_Vbo(NULL), m_Ibo(ibo)
{}

Model::Model(const void* data, unsigned int size, VertexBufferLayout layout, IndexBuffer* ibo)
: m_Vbo(new VertexBuffer(data, size)), m_Vbo_Layout(layout), m_Ibo(ibo)
{}

Model::~Model()
{
    // TODO: nothing yet.
    for (int i=0; i<m_Vbos.size(); i++)
    {
        if (m_Vbos[i]!=NULL)
            delete m_Vbos[i];
    }
    delete m_Ibo;
}

void Model::Use()
{
    if(m_Vbo==NULL)
    {
        m_Vao.Bind(m_Vbos);
        //    m_Vao.Bind(m_Vbos[0], m_Vbos[1]);
        m_Ibo->Bind();
        return;
    }
    else
    {
        m_Vao.Bind(*m_Vbo, m_Vbo_Layout);
        m_Ibo->Bind();
    }
    
}
