//
//  Cube.cpp
//  bird
//
//  Created by 汪依尘 on 7/5/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Cube.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MeshRenderer.hpp"
#include "MeshRendererAssimp.hpp"

const char* Cube::Configuration_FilePath = "src/game/basic/script/info/mesh/MeshCube.lua";

//float Cube::DefaultModel_VertPos[6 * 4 * 8] =
//{
//    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//
//    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//    1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//    1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//
//    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
//    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
//    1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
//    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
//
//    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//    -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
//    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
//
//    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//
//    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
//    -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
//};
//
//unsigned int Cube::DefaultModel_VertIdx[6 * 6] =
//{
//    0, 1, 2, 2, 3, 0,           //front
//    4, 5, 6, 4, 6, 7,           //right
//    8, 9, 10, 8, 10, 11,        //back
//    12, 13, 14, 12, 14, 15,     //left
//    16, 17, 18, 16, 18, 19,     //upper
//    20, 21, 22, 20, 22, 23      //bottom
//};


Cube::Cube()
: GameObject("Cube")
{
    MeshRendererBind();
}

void Cube::MeshRendererBind()
{
//    AddComponent<MeshRenderer>(new MeshRenderer(this, ModelElement_Group::ModelElement_Group_Prefabs[this->GetTag()],
//                                                new Material(new Shader(Material::DefaultShader_Path[0],
//                                                           Material::DefaultShader_Path[1]))));
    
//    AddComponent<MeshRenderer>(MeshRenderer::BuildFromScript(Configuration_FilePath));
    
    AddComponent<rl::MeshRenderer>(rl::MeshRenderer::BuildFromLuaScript(this, Configuration_FilePath));
}


Cube::~Cube()
{
}

//void Cube::Update()
//{
//}

//void Cube::OnRender()
//{
//    for (auto component: GetComponents())
//    {
//        component->OnRender();
//    }
//    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
//    if (mr == NULL)
//    {
//        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
//        return;
//    }
//    //        mr->RenderPrepare();
//    rl::Shader* shaderPtr = mr->GetMaterial()->GetShader();
//    shaderPtr->Use();
//
//    ml::Vector3f camPos = DisplaySys::GetInstance()->GetMainCamera()->GetTransform()->GetPosition();
//    shaderPtr->SetUniform3f("u_CameraPos", camPos.x, camPos.y, camPos.z);
//    shaderPtr->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
//    shaderPtr->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
//
//    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
//    modelMat = ml::Scale(modelMat, GetTransform()->GetScale());
//    shaderPtr->SetUniformMat4f("u_ModelMatrix", modelMat);
//
//    mr->Draw();
//}

//void Cube::OnRenderOutline()
//{
//    for (auto component: GetComponents())
//    {
//        component->OnRender();
//    }
//    /****** first pass *****/
//    GLCALL(glEnable(GL_STENCIL_TEST));
//    GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
//    GLCALL(glStencilMask(0xFF));
//    OnRender();
//
//    /****** second pass *****/
//    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
//    if (mr == NULL)
//    {
//        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
//        return;
//    }
//    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
//    GLCALL(glStencilMask(0x00));
//    GLCALL(glDisable(GL_DEPTH_TEST));
//
//    rl::Shader::PlainShader->Use();
//    rl::Shader::PlainShader->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
//    rl::Shader::PlainShader->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
//
//    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
//    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
//    modelMat = ml::Scale(modelMat, GetTransform()->GetScale() * 1.1f);
//    rl::Shader::PlainShader->SetUniformMat4f("u_ModelMatrix", modelMat);
//
//    mr->DrawOutline();
//
//    GLCALL(glStencilMask(0xFF));
//    GLCALL(glEnable(GL_DEPTH_TEST));
//    GLCALL(glDisable(GL_STENCIL_TEST));
//}


