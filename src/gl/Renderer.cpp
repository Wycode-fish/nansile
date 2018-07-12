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

Renderer::Renderer()
{
    
}
Renderer::~Renderer()
{
    
}

void Renderer::Draw(Model& model) const
{
    GLCALL(glDrawElements(GL_TRIANGLES, model.GetCount(), GL_UNSIGNED_INT, nullptr));
}

//void Renderer::DrawOutLine(Model& model) const
//{
//    
//}

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

void Renderer::Render(Model& model, Shader& shader) const
{
    GLCALL(model.Use());
    GLCALL(shader.Use());
    Draw(model);
}

void Renderer::Render(Model& model, Shader& shader, Texture& texture) const
{
    GLCALL(model.Use());
    GLCALL(shader.Use());
    GLCALL(texture.Bind());
    Draw(model);
}

void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCALL(glBindVertexArray(0));
    GLCALL(glUseProgram(0));
}
