//
//  Renderer.hpp
//  bird
//
//  Created by 汪依尘 on 6/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <signal.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!x) raise(SIGKILL)
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GLCheckError(#x, __FILE__, __LINE__))

extern void GLClearError();
extern bool GLCheckError(const char* command, const char* filePath, const int line);

class VertexArray;
class IndexBuffer;
class VertexBuffer;
class VertexBufferLayout;
class Shader;
class Model;
class Texture;

class Renderer
{
private:
    void Draw(Model& model) const;
public:
    Renderer();
    ~Renderer();
    ////// DRAW SINGLE VBO //////
    void Render(VertexArray& vao, VertexBuffer& vbo, VertexBufferLayout& layout, IndexBuffer& ibo, Shader& shader) const;
    
    ////// DRAW MULTIPLE VBO //////
    void Render(VertexArray& vao, VertexBuffer& vpos, VertexBuffer& tcs, IndexBuffer& ibo, Shader& shader) const;
    
    ////// DRAW MODEL //////
    void Render(Model& model, Shader& shader) const;
    void Render(Model& model, Shader& shader, Texture& texture) const;
    
    void Clear() const;
};

#endif /* Renderer_hpp */
