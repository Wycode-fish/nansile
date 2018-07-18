//
//  GameObject.cpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "GameObject.hpp"


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
    m_Transform->SetLocalScale(glm::vec3(t_SizeX, t_SizeY, t_SizeZ));
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
    m_Transform->SetScale(m_Transform->GetLocalScale() * m_Parent->GetTransform()->GetScale());
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
    
}
