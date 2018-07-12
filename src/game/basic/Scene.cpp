//
//  Scene.cpp
//  bird
//
//  Created by 汪依尘 on 7/6/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Scene.hpp"
#include "GameObject.hpp"

Scene::Scene()
:m_GameObjects(std::vector<GameObject*>())
{
    
}

Scene::~Scene()
{
    for (int i=0; i<m_GameObjects.size(); i++)
    {
        if (m_GameObjects[i]!=NULL)
            delete m_GameObjects[i];
    }
}

void Scene::Update()
{
    for (int i=0; i<m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Update();
    }
}

void Scene::Render()
{
    for (int i=0; i<m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->OnRender();
    }
}

void Scene::AddGameObject(GameObject *gameObject)
{

    if (m_GameObjectCounter.find(gameObject->GetTag()) != m_GameObjectCounter.end())
        m_GameObjectCounter.find(gameObject->GetTag())->second += 1;
    else
        m_GameObjectCounter[gameObject->GetTag()] = 1;
    
    std::string name = std::string(gameObject->GetTag())+std::to_string(m_GameObjectCounter[gameObject->GetTag()]);
    
    gameObject->SetName(name.c_str());
//    m_ObjNames.push_back(name.c_str());
    m_GameObjects.push_back(gameObject);
    
//    std::cout<<m_GameObjects[m_GameObjects.size()-1]->GetName()<<std::endl;
}
