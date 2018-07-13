//
//  MeshRendererPanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "MeshRendererPanel.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <gtc/type_ptr.hpp>
#include "ResourceManager.hpp"

namespace gui {
    MeshRendererPanel::MeshRendererPanel( MeshRenderer* meshRenderer)
    : m_MeshRenderer(meshRenderer)
    {
        
    }
    MeshRendererPanel::~MeshRendererPanel()
    {
        
    }
    
    void MeshRendererPanel::OnRender()
    {
        ImGui::CollapsingHeader("MESH RENDERER");
        
        m_OnRender_MaterialEdit();
        
        m_OnRender_TextureSelect();
        
    }
    
    void MeshRendererPanel::OnUpdate()
    {

    }
    
    void MeshRendererPanel::m_OnRender_MaterialEdit()
    {
        if (ImGui::TreeNode("MATERIAL"))
        {
            ImGui::SliderFloat3("ambient",
                                glm::value_ptr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatAmbientRef()), 0.0f, 1.0f);
            ImGui::SliderFloat3("diffuse",
                                glm::value_ptr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatDiffuseRef()), 0.0f, 1.0f);
            ImGui::SliderFloat3("specular", glm::value_ptr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatSpecularRef()), 0.0f, 1.0f);
            ImGui::SliderFloat("shiness", &m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatShinessRef(), 0.0f, 256.0f);
            if (ImGui::Button("reset"))
            {
                m_MeshRenderer->GetMaterial()->GetAttribs()->ResetMatAttribs();
            }
            ImGui::TreePop();
        }

    }
    
    void MeshRendererPanel::m_OnRender_TextureSelect()
    {
        if (ImGui::TreeNode("TEXTURE"))
        {
            int map_size = ResourceManager::GetTextureResourceMap().size();
            
            std::vector<const char*> texNames;
            for (auto pair: ResourceManager::GetTextureResourceMap())
            {
                char* str = new char[pair.first.length()+1];
                strcpy(str, pair.first.c_str());
                texNames.push_back(str);
            }
            
            texNames.push_back("Standard");
            ImGui::ListBox("", &m_CurrSelectedTexture, texNames.data(), map_size + 1);
            ImGui::SameLine(); ShowHelpMarker("select texture.");
            
            if (ImGui::Button("use") && (m_CurrSelectedTexture>=0 && m_CurrSelectedTexture<map_size + 1))
            {
                const char* curr_selectedTextureName = texNames[m_CurrSelectedTexture];
                auto curr_texture = m_MeshRenderer->GetMaterial()->GetTexture();
                
                if ( curr_texture!=NULL && strcmp(curr_selectedTextureName, "Standard")==0)
                    m_MeshRenderer->GetMaterial()->SetTexture(NULL);
                
                else if ( curr_texture==NULL ||
                         strcmp(curr_texture->GetFilePath(), curr_selectedTextureName) != 0)
                {
                    m_MeshRenderer->GetMaterial()->SetTexture(Texture::GetTexture(curr_selectedTextureName));
                }
            }
            ImGui::TreePop();
            
            for (int i=0; i<map_size; i++)
            {
                if (texNames[i]!=NULL)
                    delete texNames[i];
            }
        }
    }
}
