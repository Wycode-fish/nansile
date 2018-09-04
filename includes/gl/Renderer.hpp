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
#define GLCALL(x) rl::GLClearError();\
x;\
ASSERT(rl::GLCheckError(#x, __FILE__, __LINE__))

#define DRAW_MODE_LINES     0x01
#define DRAW_MODE_TRIANGLES 0x00

namespace rl {
    
    extern void GLClearError();
    extern bool GLCheckError(const char* command, const char* filePath, const int line);

    class VertexArray;
    class IndexBuffer;
    class VertexBuffer;
    class VertexBufferLayout;
    class Shader;
    class Mesh;
    class Texture;

    class Renderer
    {
    public:
        void Draw(rl::Mesh& mesh) const;
        void DrawLines(rl::Mesh& mesh) const;
        void DrawInstances(rl::Mesh& mesh, unsigned instanceNum) const;
    public:
        Renderer( const unsigned char& drawMode = DRAW_MODE_TRIANGLES);
        ~Renderer();
        ////// DRAW SINGLE VBO //////
        void Render(VertexArray& vao, VertexBuffer& vbo, VertexBufferLayout& layout, IndexBuffer& ibo, Shader& shader) const;
        
        ////// DRAW MULTIPLE VBO //////
        void Render(VertexArray& vao, VertexBuffer& vpos, VertexBuffer& tcs, IndexBuffer& ibo, Shader& shader) const;
        
        ////// DRAW MODEL //////
        void Render(rl::Mesh& mesh, Shader& shader) const;
        void Render(rl::Mesh& mesh, Shader& shader, Texture& texture) const;
        
        void Clear() const;
        
    public:
        inline unsigned char  GetDrawMode() const { return m_DrawMode; }
        inline void           SetDrawMode(const unsigned char& mode) { m_DrawMode = mode; }
        
    private:
        unsigned char m_DrawMode;
    };
}
#endif /* Renderer_hpp */
