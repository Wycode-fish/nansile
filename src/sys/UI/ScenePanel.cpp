//
//  ScenePanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ScenePanel.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "GameObjectPanel.hpp"
#include "DisplaySys.hpp"
#include "MeshRenderer.hpp"
#include "MeshRendererAssimp.hpp"
#include "Camera.hpp"
#include <string>

namespace gui {
    ScenePanel::ScenePanel( Scene* scene)
    : m_Scene(scene), m_GameObjectPanel(NULL), m_CurrSelected(0)
    {
        m_GameObjectPanel = new GameObjectPanel(m_Scene->GetGameObjects()[m_CurrSelected]);
    }
    
    ScenePanel::~ScenePanel()
    {
        
    }
    
    void ScenePanel::OnRender()
    {
        ImGui::Begin("SCENE");
        auto objs = m_Scene->GetGameObjects();
        std::vector<const char*> objNames;
        for (auto obj : objs)
        {
            std::string str = obj->GetName();
            char * cstr = new char [str.length()+1];
            std::strcpy (cstr, str.c_str());
            objNames.push_back(cstr);
        }
        
        ImGui::ListBox("", &m_CurrSelected, objNames.data(), static_cast<int>(objs.size()));
        ImGui::SameLine(); ShowHelpMarker("select game objects.");
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        int generatorsSize = static_cast<int>(ResourceManager::GetGenerators().names.size());
        ImGui::Combo("", &m_CurrToBeCreated,
                     ResourceManager::GetGenerators().names.data(),
                     generatorsSize);
        
        if (ImGui::Button("new") && (m_CurrToBeCreated >= 0 && m_CurrToBeCreated < generatorsSize))
        {
            m_Scene->AddGameObject(ResourceManager::GetGenerators().generators[m_CurrToBeCreated]());
        }
        for (int i=1; i<objNames.size(); i++)
        {
            if (objNames[i]!=NULL)
                delete objNames[i];
        }
        
        ImGui::Text("Application average %.2f FPS", ImGui::GetIO().Framerate);

        ImGui::End();
        
        m_GameObjectPanel->OnRender();
    }
    
    
    void ScenePanel::OnUpdate()
    {
        if (m_GameObjectPanel->GetGameObject() != m_Scene->GetGameObjects()[m_CurrSelected])
        {
            m_Scene->SetSelectedGameObject(m_CurrSelected);
            
//            GameObject* selectedGameObj = m_Scene->GetGameObjects()[m_CurrSelected];
//
//            if (m_GameObjectPanel->GetGameObject() != DisplaySys::GetInstance()->GetMainCamera())
//            {
//                ml::Vector3f posOffset = ml::Vector3f(0.0f, 0.0f, (10) * selectedGameObj->GetTransform()->GetScale().z);
//                DisplaySys::GetInstance()->GetMainCamera()->GetTransform()->SetPosition(selectedGameObj->GetTransform()->GetPosition() + posOffset);
//                DisplaySys::GetInstance()->GetMainCamera()->GetTransform()->SetRotation(selectedGameObj->GetTransform()->GetPosition() - DisplaySys::GetInstance()->GetMainCamera()->GetTransform()->GetPosition());
//            }
//
//            rl::MeshRenderer* mr_curr;
//            if ((mr_curr = m_GameObjectPanel->GetGameObject()->GetComponent<rl::MeshRenderer>()) != NULL)
//            {
//                mr_curr->GetMaterial()->GetAttribs()->Dimmer();
//            }
//            rl::MeshRenderer* mr_new;
//            if ((mr_new = selectedGameObj->GetComponent<rl::MeshRenderer>()) != NULL)
//            {
//                mr_new->GetMaterial()->GetAttribs()->Brighter();
//            }
            m_GameObjectPanel->BindGameObject(m_Scene->GetGameObjects()[m_CurrSelected]);
            
        }
        
        m_GameObjectPanel->OnUpdate();
    }
}
