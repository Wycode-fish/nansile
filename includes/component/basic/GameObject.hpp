//
//  GameObject.hpp
//  bird
//
//  Created by 汪依尘 on 6/16/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Component.hpp"
#include "Transform.hpp"

extern float VWidth;
extern float VHeight;
extern float VHWRatio;

class MeshRenderer;

class GameObject
{
public:
    GameObject();
    GameObject(const char* tag);
    virtual ~GameObject();
    
public:
    virtual void Update();
    virtual void OnRender();
    
public:
    virtual void MeshRendererBind();
    virtual void ColliderBind();
    
public:
    inline Transform* GetTransform() const { return m_Transform; }
    inline GameObject* GetParent() const { return m_Parent; }
    inline std::vector<Component*> GetComponents() const { return m_Components; }
    inline std::vector<GameObject*> GetChilds() const { return m_Childs;}
    inline const char* GetTag() const { return m_Tag; }
    inline std::string GetName() const { return m_Name; }
    inline void SetName(const char* name) { m_Name = name; }
    
public:
    void GlobalTransformUpdate();
    
public:
    template<typename T>
    T* GetComponent()
    {
        for(int i=0; i<m_Components.size(); i++)
        {
            T* temp;
            if ((temp = dynamic_cast<T*>(m_Components[i])))
                return temp;
        }
        return NULL;
    }
    
    template<typename T>
    void AddComponent(T* component)
    {
        Component* temp = dynamic_cast<Component*>(component);
        if (temp!=NULL)
            m_Components.push_back(temp);
        else
            std::cout<<"[INFO]: "<<__FILE__<<", AddComponent() failed."<<std::endl;
    }
public:
    template<typename T>
    void AddChild(T* child)
    {
        GameObject* temp = dynamic_cast<GameObject*>(child);
        if (temp!=NULL)
        {
            m_Childs.push_back(temp);
            temp->OnAddChild(this);
        }
        else
            std::cout<<"[INFO]: "<<__FILE__<<", AddChild() failed."<<std::endl;
    }
    
    template<typename T>
    void OnAddChild(T* parent)
    {
        GameObject* temp = dynamic_cast<GameObject*>(parent);
        if (temp!=NULL)
        {
            m_Parent = temp;
            m_LocalTransformUpdate(*m_Parent);
        }
        else
            std::cout<<"[INFO]: "<<__FILE__<<", OnAddChild() failed."<<std::endl;
    }
    
    template<typename T>
    T* GetChild()
    {
        for(int i=0; i<m_Childs.size(); i++)
        {
            T* temp;
            if ((temp = dynamic_cast<T*>(m_Childs[i])))
                return temp;
        }
        return NULL;
    }
    
private:    // After parent-child ops.
    void m_LocalTransformUpdate(GameObject& parent);
    
private:    // After local transform update.
    void m_GlobalPositionUpdate();
    void m_GlobalScaleUpdate();
    void m_GlobalRotationUpdate();
    
private:
    Transform* m_Transform;
    GameObject* m_Parent;
    std::vector<GameObject*> m_Childs;
    std::vector<Component*> m_Components;
private:
    const char* m_Tag;
    std::string m_Name;
};
#endif /* GameObject_hpp */
