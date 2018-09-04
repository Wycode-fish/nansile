//
//  GameObject.cpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Component.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "MeshRendererAssimp.hpp"
#include "Material.hpp"

float VHWRatio = 9.0f / 16.0f;
float VWidth = 10.0f;
float VHeight = VWidth * VHWRatio;

//std::vector<GameObject*> GameObject::sm_RenderList;

GameObject::GameObject()
: m_Transform(NULL), m_Parent(NULL), m_Tag("default"), m_Name(m_Tag)
{
    m_Transform = new Transform();
}

GameObject::GameObject(const char* tag)
: m_Transform(NULL), m_Parent(NULL), m_Tag(tag), m_Name(m_Tag)
{
    m_Transform = new Transform();
}

GameObject::~GameObject()
{
    for (int i=0; i<m_Components.size(); i++)
    {
        if (m_Components[i]!=NULL)
            delete m_Components[i];
    }
    
    for (int i=0; i<m_Childs.size(); i++)
    {
        if (m_Childs[i]!=NULL)
            delete m_Childs[i];
    }
    if (m_Parent!=NULL)
        delete m_Parent;
    
    if (m_Transform!=NULL)
        delete m_Transform;
}

void GameObject::MeshRendererBind()
{
    
}

void GameObject::ColliderBind()
{
    
}

void GameObject::m_LocalTransformUpdate(GameObject& parent)
{
    m_Transform->SetLocalPosition(m_Transform->GetPosition() - parent.GetTransform()->GetPosition());
    
    float t_SizeX = m_Transform->GetScale().x/parent.GetTransform()->GetScale().x;
    float t_SizeY = m_Transform->GetScale().y/parent.GetTransform()->GetScale().y;
    float t_SizeZ = m_Transform->GetScale().z/parent.GetTransform()->GetScale().z;
    m_Transform->SetLocalScale(ml::Vector3f(t_SizeX, t_SizeY, t_SizeZ));
    // TODO: Local Rotation update.
}


void GameObject::GlobalTransformUpdate()
{
    m_GlobalScaleUpdate();
    m_GlobalRotationUpdate();
    m_GlobalPositionUpdate();
}

void GameObject::m_GlobalPositionUpdate()
{
    m_Transform->SetPosition(m_Transform->GetLocalPosition() + m_Parent->GetTransform()->GetPosition());
    for (int i=0; i<m_Childs.size(); i++)
    {
        m_Childs[i]->m_GlobalPositionUpdate();
    }
}

void GameObject::m_GlobalRotationUpdate()
{
    // TODO: global rotation update.
}


void GameObject::m_GlobalScaleUpdate()
{
    m_Transform->SetScale(m_Parent->GetTransform()->GetScale() * m_Transform->GetLocalScale());
    for (int i=0; i<m_Childs.size(); i++)
    {
        m_Childs[i]->m_GlobalScaleUpdate();
    }
}

void GameObject::Update()
{
    for (Component* component : GetComponents())
    {
        component->Update();
    }
}

void GameObject::OnRender()
{
    for (auto component: GetComponents())
    {
        component->OnRender();
    }
    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
    if (mr == NULL)
    {
        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
        return;
    }
    //        mr->RenderPrepare();
    rl::Shader* shaderPtr = mr->GetMaterial()->GetShader();
    shaderPtr->Use();
    
    ml::Vector3f camPos = DisplaySys::GetInstance()->GetMainCamera()->GetTransform()->GetPosition();
    shaderPtr->SetUniform3f("u_CameraPos", camPos.x, camPos.y, camPos.z);
    shaderPtr->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
    shaderPtr->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
    
    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
    modelMat = ml::Scale(modelMat, GetTransform()->GetScale());
    shaderPtr->SetUniformMat4f("u_ModelMatrix", modelMat);
    
    mr->Draw();
}

void GameObject::OnRenderOutline()
{
    for (auto component: GetComponents())
    {
        component->OnRender();
    }
    /****** first pass *****/
    GLCALL(glEnable(GL_STENCIL_TEST));
    GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    GLCALL(glStencilMask(0xFF));
    OnRender();
    
    /****** second pass *****/
    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
    if (mr == NULL)
    {
        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
        return;
    }
    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GLCALL(glStencilMask(0x00));
    GLCALL(glDisable(GL_DEPTH_TEST));
    
    rl::Shader::PlainShader->Use();
    rl::Shader::PlainShader->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
    rl::Shader::PlainShader->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
    
    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
    modelMat = ml::Scale(modelMat, GetTransform()->GetScale() * 1.01f);
    rl::Shader::PlainShader->SetUniformMat4f("u_ModelMatrix", modelMat);
    
    mr->DrawOutline();
    
    GLCALL(glStencilMask(0xFF));
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glDisable(GL_STENCIL_TEST));
}


