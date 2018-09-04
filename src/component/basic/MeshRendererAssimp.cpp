//
//  MeshRendererAssimp.cpp
//  bird
//
//  Created by 汪依尘 on 8/12/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "MeshRendererAssimp.hpp"
#include "ResourceManager.hpp"
#include <iostream>

#include "GameObject.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "TextEditor.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "LuaScript.hpp"

namespace rl {
    
    MeshRenderer* MeshRenderer::BuildFromLuaScript( GameObject* thz, const char* scriptPath)
    {
        Model* model = new Model(scriptPath);
        Material* mat = new Material(scriptPath);
        return new MeshRenderer(thz, model, mat);
    }

    
    MeshRenderer::MeshRenderer( GameObject* thz, Model* model, Material* mat)
    : m_Model(model), m_Material(mat), m_Renderer(new Renderer()), m_IsActive(true), m_ActiveMode(DRAW_MODE_TRIANGLES), Component(thz, "Mesh Renderer")
    {}
    
    MeshRenderer::~MeshRenderer()
    {
        if (m_Material != nullptr)
            delete m_Material;
        if (m_Model != nullptr)
            delete m_Model;
    }
    
    void MeshRenderer::Update()
    {
        if (m_IsActive)
        {
            if (m_ActiveMode == DRAW_MODE_TRIANGLES)
            {
                m_Renderer->SetDrawMode(DRAW_MODE_TRIANGLES);
            }
            else
            {
                m_Renderer->SetDrawMode(DRAW_MODE_LINES);
            }
        }
        else
        {
            m_Renderer->SetDrawMode(DRAW_MODE_LINES);
        }
    }
    
    void MeshRenderer::ApplyLight(Light* light) const
    {
        ml::Vector3f ambient = light->GetAttribs()->m_Ambient;
        ml::Vector3f diffuse = light->GetAttribs()->m_Diffuse;
        ml::Vector3f specular = light->GetAttribs()->m_Specular;
        ml::Vector3f attenuation = light->GetAttribs()->m_Attenuation;
        ml::Vector3f color = light->GetAttribs()->m_Color;
        float intensity = light->GetAttribs()->m_Intensity;
        
        ml::Vector3f pos = light->GetTransform()->GetPosition();
        ml::Vector3f rot = light->GetTransform()->GetRotation();
        
        rl::Shader* shaderPtr = m_Material->GetShader();
        shaderPtr->Use();
        if ( shaderPtr->SetUniform3f("u_LightPos", pos.x, pos.y, pos.z) )
        {
            shaderPtr->SetUniform3f("u_LightDirection", rot.x, rot.y, rot.z);
            shaderPtr->SetUniform3f("u_LightColor", color.x, color.y, color.z);
            shaderPtr->SetUniform1i("u_LightType", light->GetType());
            
            shaderPtr->SetUniform3f("u_Light.ambient", ambient.x, ambient.y, ambient.z);
            shaderPtr->SetUniform3f("u_Light.diffuse", diffuse.x, diffuse.y, diffuse.z);
            shaderPtr->SetUniform3f("u_Light.specular", specular.x, specular.y, specular.z);
            shaderPtr->SetUniform1f("u_Light.attenuation_Kc", attenuation[ATTENUATION_KC]);
            shaderPtr->SetUniform1f("u_Light.attenuation_Kl", attenuation[ATTENUATION_KL]);
            shaderPtr->SetUniform1f("u_Light.attenuation_Kq", attenuation[ATTENUATION_KQ]);
            shaderPtr->SetUniform1f("u_Light.intensity", intensity);
        }
        
    }
    
    void MeshRenderer::RenderPrepare() const
    {
        for (int i=0; i<Light::ActiveLights.size(); i++)
        {
            ApplyLight(Light::ActiveLights[i]);
        }
    }
    
    void MeshRenderer::Draw() const
    {
        RenderPrepare();
        m_Model->Draw( m_Renderer, m_Material);
    }
    
    void MeshRenderer::DrawOutline() const
    {
        m_Model->DrawOutline( m_Renderer );
    }

    void MeshRenderer::DrawInstances( unsigned instanceNum) const
    {
        RenderPrepare();
        m_Model->DrawInstances( m_Renderer, m_Material, instanceNum );
    }
}
