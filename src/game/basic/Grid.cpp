//
//  Grid.cpp
//  bird
//
//  Created by 汪依尘 on 7/8/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Grid.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MeshRendererAssimp.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Renderer.hpp"

const char* Grid::Configuration_FilePath = "src/game/basic/script/info/mesh/MeshQuad.lua";
const unsigned Grid::Side_Length = 9;

Grid::Grid()
: GameObject("Grid")
{
    MeshRendererBind();
    GetComponent<rl::MeshRenderer>()->SetRendererMode(DRAW_MODE_LINES);
    GetComponent<rl::MeshRenderer>()->SetActiveRendererMode(DRAW_MODE_LINES);
    
    for (int i=0; i<Side_Length; i++ )
    {
        for (int j=0; j<Side_Length; j++)
        {
            m_Translations[i * Side_Length + j] = ml::Vector3f(j - 4, 0.0f, i - 4);
        }
    }
    m_InstanceVBOInit(m_Translations);
}

void Grid::m_InstanceVBOInit( ml::Vector3f translation[])
{
    GLCALL(glGenBuffers(1, &m_InstanceVBO));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstanceVBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(ml::Vector3f) * Side_Length * Side_Length, &translation[0], GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Grid::MeshRendererBind()
{
    AddComponent<rl::MeshRenderer>(rl::MeshRenderer::BuildFromLuaScript(this, Configuration_FilePath));
}


Grid::~Grid()
{
}

void Grid::OnRender()
{
    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
    if (mr == NULL)
    {
        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
        return;
    }
    //        mr->RenderPrepare();
    rl::Shader* shaderPtr = mr->GetMaterial()->GetShader();
    shaderPtr->Use();
    
    shaderPtr->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
    shaderPtr->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
    
    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
    modelMat = ml::Scale(modelMat, GetTransform()->GetScale());
    shaderPtr->SetUniformMat4f("u_ModelMatrix", modelMat);
    
    for (auto mesh: mr->GetModel()->GetMeshes())
    {
        mesh->Use();
    }
    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstanceVBO));
    GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glVertexAttribDivisor(1, 1));
    
    mr->DrawInstances(Side_Length * Side_Length);
}

void Grid::OnRenderOutline()
{
}
