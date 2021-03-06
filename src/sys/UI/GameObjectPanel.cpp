//
//  GameObjectPanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "GameObjectPanel.hpp"
#include "ml.h"
#include "MeshRendererPanel.hpp"


namespace gui {
    
    std::unordered_map<std::string, std::function<ComponentPanel*(Component*)> > ComponentPanel::m_ComponentPanelGenerators = std::unordered_map<std::string, std::function<ComponentPanel*(Component*)> >();
    
    GameObjectPanel::GameObjectPanel( GameObject* gameObject)
    : m_GameObject(gameObject)
    {
        LoadComponentPanels();
    }
    
    GameObjectPanel::~GameObjectPanel()
    {
        for (int i=0; i<m_ComponentPanels.size(); i++)
        {
            if (m_ComponentPanels[i]!=NULL)
            {
                delete m_ComponentPanels[i];
            }
        }
    }
    
    
    void GameObjectPanel::LoadComponentPanels()
    {
        for (Component* component: m_GameObject->GetComponents())
        {
            std::string tag = component->GetTag().c_str();
            auto panelGeneratorLambda = ComponentPanel::GetPanelGenerators()[tag];
            if (panelGeneratorLambda == nullptr)
            {
                std::cout<<"[ERROR]: "<<tag<<" Panel Generator can not be found."<<std::endl;
                return;
            }
            m_ComponentPanels.push_back(panelGeneratorLambda(component));
        }
    }
    
    
    void GameObjectPanel::BindGameObject(GameObject* gameObject)
    {
        m_GameObject = gameObject;
        for (auto componentPanel : m_ComponentPanels)
        {
            if (componentPanel!=NULL)
                delete componentPanel;
        }
        m_ComponentPanels.clear();
        LoadComponentPanels();
    }
    
    void GameObjectPanel::OnRender()
    {
        ImGui::Begin(m_GameObject->GetName().c_str());
        
        m_OnRender_Transform();

        ImGui::NewLine();
        ImGui::Separator();
        ImGui::NewLine();
        
        for (auto componentPanel: m_ComponentPanels)
        {
            componentPanel->OnRender();
            
            ImGui::NewLine();
            ImGui::Separator();
            ImGui::NewLine();
        }
        
        ImGui::End();
    }
    
    void GameObjectPanel::m_OnRender_Transform()
    {
        ImGui::CollapsingHeader("TRANSFORM");
        ImGui::NewLine();
        
        float pi = ml::Pi<float>();
        ImGui::SliderFloat3("position", ml::ValuePtr(m_GameObject->GetTransform()->GetPositionRef()), -VWidth, VWidth);
        ImGui::SliderFloat3("rotation(PI)", ml::ValuePtr(m_GameObject->GetTransform()->GetRotationRef()), -1.0f * pi, 1.0f * pi);
        ImGui::SliderFloat3("scale", ml::ValuePtr(m_GameObject->GetTransform()->GetScaleRef()), 0.0f, VWidth);
        if (ImGui::Button("reset"))
        {
            m_GameObject->GetTransform()->SetPosition(ml::Vector3f(0.0f, 0.0f, 0.0f));
            m_GameObject->GetTransform()->SetRotation(ml::Vector3f(0.0f, 0.0f, 0.0f));
            m_GameObject->GetTransform()->SetScale(ml::Vector3f(1.0f, 1.0f, 1.0f));
        }
    }
    
    void GameObjectPanel::OnUpdate()
    {
        for (auto componentPanel: m_ComponentPanels)
        {
            componentPanel->OnUpdate();
        }
    }
}
