//
//  Renderer.cpp
//  bird
//
//  Created by 汪依尘 on 6/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include <iostream>
#include "Renderer.hpp"
#include "Model.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace rl {
    void GLClearError()
    {
        while(glGetError()){}
    }

    bool GLCheckError(const char* func, const char* path, const int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout<<"[OpenGL]: "<<func<<", "<<path<<": "<<line<<", ERRCODE: "<<error<<std::endl;
            return false;
        }
        return true;
    }

    Renderer::Renderer(const unsigned char& drawMode)
    : m_DrawMode(drawMode)
    {
        
    }
    Renderer::~Renderer()
    {
        
    }

    void Renderer::Draw(Mesh& mesh) const
    {
        GLCALL(glDrawElements(GL_TRIANGLES, mesh.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::DrawLines(Mesh& mesh) const
    {
        GLCALL(glDrawElements(GL_LINE_LOOP, mesh.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::DrawInstances(rl::Mesh& mesh, unsigned instanceNum) const
    {
        if (m_DrawMode == DRAW_MODE_LINES)
        {
            GLCALL(glDrawElementsInstanced(GL_LINE_LOOP, mesh.GetCount(), GL_UNSIGNED_INT, nullptr, instanceNum));
        }
        else if (m_DrawMode == DRAW_MODE_TRIANGLES)
        {
            GLCALL(glDrawElementsInstanced(GL_TRIANGLES, mesh.GetCount(), GL_UNSIGNED_INT, nullptr, instanceNum));
        }
    }

    
    void Renderer::Render(VertexArray& vao, VertexBuffer& vbo, VertexBufferLayout& layout, IndexBuffer& ibo, Shader& shader) const
    {
        GLCALL(vao.Bind(vbo, layout));
        GLCALL(ibo.Bind());
        GLCALL(shader.Use());
        GLCALL(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::Render(VertexArray& vao, VertexBuffer& vpos, VertexBuffer& tcs, IndexBuffer& ibo, Shader& shader) const
    {
        GLCALL(vao.Bind(vpos, tcs));
        GLCALL(ibo.Bind());
        GLCALL(shader.Use());
        GLCALL(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::Render(rl::Mesh& mesh, Shader& shader) const
    {
        GLCALL(mesh.Use());
        GLCALL(shader.Use());
        Draw(mesh);
    }

    void Renderer::Render(rl::Mesh& mesh, Shader& shader, Texture& texture) const
    {
        GLCALL(shader.Use());
        GLCALL(texture.Bind());
        GLCALL(mesh.Use());
        Draw(mesh);
    }

    void Renderer::Clear() const
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GLCALL(glBindVertexArray(0));
        GLCALL(glUseProgram(0));
    }
    
}
