//
//  MeshRendererPanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "MeshRendererPanel.hpp"
#include "ml.h"
#include "ResourceManager.hpp"
#include "Material.hpp"
#include "TextEditor.hpp"
#include "Model.hpp"

namespace gui {
    
    MeshEditor::MeshEditor(rl::Mesh* mesh)
    : m_Mesh(mesh), m_CurrSelectedTexture(0)
    {}
    
    MeshEditor::~MeshEditor()
    {}
    
    void MeshEditor::OnRender()
    {
        if (ImGui::TreeNode("TEXTURE"))
        {
            int map_size = static_cast<int>(ResourceManager::GetTextureResourceMap().size());
            
            std::vector<const char*> texNames;
            for (auto pair: ResourceManager::GetTextureResourceMap())
            {
                texNames.push_back(TextEditor::Str2ValuePtr(pair.first));
            }
            
            texNames.push_back("standard");
            ImGui::ListBox("", &m_CurrSelectedTexture, texNames.data(), map_size + 1);
            ImGui::SameLine(); ShowHelpMarker("select texture.");
            
            if (ImGui::Button("use") && (m_CurrSelectedTexture>=0 && m_CurrSelectedTexture<map_size + 1))
            {
                const char* curr_selectedTextureName = texNames[m_CurrSelectedTexture];
                auto curr_texture_0 = (m_Mesh->GetTextures().size() == 0)? NULL: m_Mesh->GetTextures()[0];
                
                if ( curr_texture_0!=NULL && strcmp(curr_selectedTextureName, "standard")==0)
                    m_Mesh->SetTextureAtPos(0, NULL);
                
                else if ( curr_texture_0==NULL ||
                         strcmp(curr_texture_0->GetFilePath(), curr_selectedTextureName) != 0)
                {
                    m_Mesh->SetTextureAtPos(0, rl::Texture::GetTexture(curr_selectedTextureName));
                }
            }
            ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();
            ImGui::TreePop();
            
            for (int i=0; i<map_size; i++)
            {
                if (texNames[i]!=NULL)
                    delete texNames[i];
            }
        }
    }
    
    void MeshEditor::OnUpdate()
    {

    }
    
    ModelEditor::ModelEditor( rl::Model* model)
    : m_Model(model), m_CurrSelectedMeshEditor(nullptr), m_CurrSeletedMesh(0), m_CurrToBeCreatedMesh(0)
    {}
    
    ModelEditor::~ModelEditor()
    {
        if (m_CurrSelectedMeshEditor != nullptr)
            delete m_CurrSelectedMeshEditor;
    }
    
    void ModelEditor::OnRender()
    {
        if (ImGui::TreeNode("MODEL"))
        {
            unsigned meshIdx = 0;
            std::vector<const char*> meshNames;
            for (rl::Mesh* mesh: m_Model->GetMeshes())
            {
                meshNames.push_back(TextEditor::Str2ValuePtr("mesh"+std::to_string(meshIdx++)));
            }
            ImGui::ListBox("", &m_CurrToBeCreatedMesh, meshNames.data(), meshIdx);
            if (m_CurrSelectedMeshEditor != nullptr)
            {
                m_CurrSelectedMeshEditor->OnRender();
            }
            for (auto str: meshNames)
            {
                if (str!=NULL)
                {
                    delete str;
                }
            }
            ImGui::TreePop();
        }
    }
    
    void ModelEditor::OnUpdate()
    {
        if ( m_CurrSelectedMeshEditor == nullptr || m_CurrToBeCreatedMesh != m_CurrSeletedMesh )
        {
            MeshEditor* temp = m_CurrSelectedMeshEditor;
            m_CurrSelectedMeshEditor = new MeshEditor( m_Model->GetMeshes()[m_CurrToBeCreatedMesh] );
            delete temp;
            
            m_CurrSeletedMesh = m_CurrToBeCreatedMesh;
        }
    }
    
    MeshRendererPanel::MeshRendererPanel( rl::MeshRenderer* meshRenderer)
    : m_MeshRenderer(meshRenderer), m_ModelEditor(new ModelEditor(meshRenderer->GetModel()))
    {}
    
    MeshRendererPanel::~MeshRendererPanel()
    {
        if (m_ModelEditor != nullptr)
            delete m_ModelEditor;
    }
    
    void MeshRendererPanel::OnRender()
    {
        ImGui::CollapsingHeader("MESH RENDERER");
        ImGui::Checkbox("active", &m_MeshRenderer->GetIsActive());
        
        m_OnRender_MaterialEdit();
        m_ModelEditor->OnRender();
//        m_OnRender_TextureSelect();
        
    }
    
    void MeshRendererPanel::OnUpdate()
    {
        m_ModelEditor->OnUpdate();
        
//        if (m_TextureActive && !m_TextureActive_Selected)
//        {
//            m_MeshRenderer->GetMaterial()->SetShader(new rl::Shader( rl::Material::DefaultShader_Path[0], rl::Material::DefaultShader_Path[1]));
//        }
//        else if (!m_TextureActive && m_TextureActive_Selected)
//        {
//            m_MeshRenderer->GetMaterial()->SetShader(new rl::Shader( rl::Material::NoneTexShader_Path[0], rl::Material::NoneTexShader_Path[1]));
//        }
//        m_TextureActive = m_TextureActive_Selected;
    }
    
    
    void MeshRendererPanel::m_OnRender_MaterialEdit()
    {
        if (ImGui::TreeNode("MATERIAL"))
        {
            ImGui::SliderFloat3("ambient",
                                ml::ValuePtr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatAmbientRef()),
                                0.0f, 1.0f);
            ImGui::SliderFloat3("diffuse",
                                ml::ValuePtr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatDiffuseRef()), 0.0f, 1.0f);
            ImGui::SliderFloat3("specular", ml::ValuePtr(m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatSpecularRef()), 0.0f, 1.0f);
            ImGui::SliderFloat("shiness", &m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatShinessRef(), 0.0f, 256.0f);
            ImGui::SliderFloat("transparency", &m_MeshRenderer->GetMaterial()->GetAttribs()->GetMatTransparencyRef(), 0.0f, 1.0f);

            if (ImGui::Button("reset"))
            {
                m_MeshRenderer->GetMaterial()->GetAttribs()->ResetMatAttribs();
            }
            ImGui::TreePop();
        }

    }
    
//    void MeshRendererPanel::m_OnRender_ModelEdit()
//    {
//        if (ImGui::TreeNode("MODEL"))
//        {
//            unsigned meshIdx = 0;
//            std::vector<const char*> meshNames;
//            for (rl::Mesh* mesh: m_MeshRenderer->GetModel()->GetMeshes())
//            {
//                meshNames.push_back(TextEditor::Str2ValuePtr("mesh"+std::to_string(meshIdx)));
//            }
//            ImGui::ListBox("", &m_CurrSelectedMesh, meshNames.data(), meshIdx + 1);
//            if (ImGui::Button("view") && (m_CurrSelectedMesh >= 0 && m_CurrSelectedMesh < meshIdx + 1))
//            {
//                m_OnRender_MeshSelected();
//            }
//
//            for (auto str: meshNames)
//            {
//                if (str!=NULL)
//                {
//                    delete str;
//                }
//            }
//            ImGui::TreePop();
//
//        }
//    }
//
//    void MeshRendererPanel::m_OnRender_MeshSelected()
//    {
//        m_OnRender_TextureSelect();
//    }
//
//
//    void MeshRendererPanel::m_OnRender_TextureSelect()
//    {
//        if (ImGui::TreeNode("TEXTURE"))
//        {
//            int map_size = static_cast<int>(ResourceManager::GetTextureResourceMap().size());
//
//            std::vector<const char*> texNames;
//            for (auto pair: ResourceManager::GetTextureResourceMap())
//            {
//                texNames.push_back(TextEditor::Str2ValuePtr(pair.first));
//            }
//
//            texNames.push_back("standard");
//            ImGui::ListBox("", &m_CurrSelectedTexture, texNames.data(), map_size + 1);
//            ImGui::SameLine(); ShowHelpMarker("select texture.");
//
//            if (ImGui::Button("use") && (m_CurrSelectedTexture>=0 && m_CurrSelectedTexture<map_size + 1))
//            {
//                const char* curr_selectedTextureName = texNames[m_CurrSelectedTexture];
//                auto curr_texture = m_MeshRenderer->GetMaterial()->GetTexture();
//
//                if ( curr_texture!=NULL && strcmp(curr_selectedTextureName, "standard")==0)
//                    m_MeshRenderer->GetMaterial()->SetTexture(NULL);
//
//                else if ( curr_texture==NULL ||
//                         strcmp(curr_texture->GetFilePath(), curr_selectedTextureName) != 0)
//                {
//                    m_MeshRenderer->GetMaterial()->SetTexture( rl::Texture::GetTexture(curr_selectedTextureName));
//                }
//            }
//            ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();
//            ImGui::Checkbox("none", &m_TextureActive_Selected);
//            ImGui::TreePop();
//
//            for (int i=0; i<map_size; i++)
//            {
//                if (texNames[i]!=NULL)
//                    delete texNames[i];
//            }
//        }
//    }
}
