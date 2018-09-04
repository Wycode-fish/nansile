//
//  ParticleSystemPanel.cpp
//  bird
//
//  Created by 汪依尘 on 8/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ParticleSystemPanel.hpp"
#include "TextEditor.hpp"
namespace gui{
    ParticleSystemPanel::ParticleSystemPanel( ParticleSystem* particleSystem)
    : m_ParticleSystem(particleSystem), m_CurrParticleCnt(static_cast<int>(m_ParticleSystem->GetParticleCnt()))
    {}

    ParticleSystemPanel::~ParticleSystemPanel()
    {}

    void ParticleSystemPanel::OnRender()
    {
        ImGui::CollapsingHeader("PARTICLE SYSTEM");
        
        if (ImGui::TreeNode("transform"))
        {
            ImGui::SliderFloat3("position", ml::ValuePtr(m_ParticleSystem->GetParticleObj()->GetTransform()->GetPositionRef()), -10.0f, 10.0f);
            
            float pi = ml::Pi<float>();
            ImGui::SliderFloat3("rotation(PI)", ml::ValuePtr(m_ParticleSystem->GetParticleObj()->GetTransform()->GetRotationRef()), -1.0f * pi, 1.0f * pi);

            ImGui::SliderFloat3("scale", ml::ValuePtr(m_ParticleSystem->GetParticleObj()->GetTransform()->GetScaleRef()), 0.0f, 10.0f);
            
            if (ImGui::Button("reset"))
            {
                m_ParticleSystem->GetParticleObj()->GetTransform()->SetPosition(ml::Vector3f(0.0f, 0.0f, 0.0f));
                m_ParticleSystem->GetParticleObj()->GetTransform()->SetRotation(ml::Vector3f(0.0f, 0.0f, 0.0f));
                m_ParticleSystem->GetParticleObj()->GetTransform()->SetScale(ml::Vector3f(1.0f, 1.0f, 1.0f));
            }
            
            ImGui::TreePop();
        }
        
        if (ImGui::TreeNode("basic params"))
        {
            ImGui::SliderFloat("particle life", &m_ParticleSystem->GetParticleLifeRef(), 0.0f, 20.0f);
            ImGui::SliderFloat("alpha decay", &m_ParticleSystem->GetAlphaDecayRef(), 0.0f, 5.0f);
            ImGui::SliderFloat("speed decay", &m_ParticleSystem->GetSpeedDecayFactorRef(), 0.0f, 5.0f);
            ImGui::SliderFloat("speed", &m_ParticleSystem->GetFloatingSpeedRef(), 0.0f, 20.0f);
            ImGui::SliderFloat("glow", &m_ParticleSystem->GetParticleObj()->GetSharpness(), 0.0f, 1.0f);
            
            ImGui::TreePop();
        }
        
        if (ImGui::TreeNode("overall"))
        {
            ImGui::SliderInt("particle count", &m_CurrParticleCnt, 0, 500);
            ImGui::SliderFloat3("color blend", ml::ValuePtr(m_ParticleSystem->GetColorPossibility()), 0.01f, 1.0f);
            
            ImGui::TreePop();
        }

    }
    void ParticleSystemPanel::OnUpdate()
    {
        if (m_ParticleSystem->GetParticleCnt() != m_CurrParticleCnt && m_CurrParticleCnt >= 0  && m_CurrParticleCnt <= 500)
        {
            std::cout<<"particle cnt update."<<std::endl;
            m_ParticleSystem->UpdateParticleCnt(static_cast<unsigned>(m_CurrParticleCnt));
        }
    }

}
