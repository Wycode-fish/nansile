//
//  Material.cpp
//  bird
//
//  Created by 汪依尘 on 7/3/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Material.hpp"
#include "LuaScript.hpp"
namespace rl{
    
    ml::Vector3f MaterialAttribs::Default_Ambient = ml::Vector3f(0.8f, 0.8f, 0.81f);
    ml::Vector3f MaterialAttribs::Default_Diffuse = ml::Vector3f(0.9f, 0.9f, 0.9f);
    ml::Vector3f MaterialAttribs::Default_Specular = ml::Vector3f(0.7f, 0.7f, 0.7f);
    float MaterialAttribs::Default_Shiness = 128.0f;
    float MaterialAttribs::Default_Transparency = 1.0f;

    MaterialAttribs::MaterialAttribs(ml::Vector3f ambient, ml::Vector3f diffuse, ml::Vector3f specular, float shiness, float transparency)
    : m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shiness(shiness), m_Transparency(transparency)
    {
    }

    void MaterialAttribs::ResetMatAttribs()
    {
        m_Ambient = Default_Ambient;
        m_Diffuse = Default_Diffuse;
        m_Specular = Default_Specular;
        m_Shiness = Default_Shiness;
        m_Transparency = Default_Transparency;
    }

    void MaterialAttribs::Brighter()
    {
        m_Ambient.x += 0.1f;
        m_Ambient.x = (m_Ambient.x > 1.0f)?1.0f:m_Ambient.x;
        m_Ambient.y += 0.1f;
        m_Ambient.y = (m_Ambient.y > 1.0f)?1.0f:m_Ambient.y;
        m_Ambient.z += 0.1f;
        m_Ambient.z = (m_Ambient.z > 1.0f)?1.0f:m_Ambient.z;
    }

    void MaterialAttribs::Dimmer()
    {
        m_Ambient.x -= 0.1f;
        m_Ambient.x = (m_Ambient.x < 0.0f)?0.0f:m_Ambient.x;
        m_Ambient.y -= 0.1f;
        m_Ambient.y = (m_Ambient.y < 0.0f)?0.0f:m_Ambient.y;
        m_Ambient.z -= 0.1f;
        m_Ambient.z = (m_Ambient.z < 0.0f)?0.0f:m_Ambient.z;
    }


    const char* Material::DefaultShader_Path[] =
    {
        "src/gl/shaders/basic/default.vertex", "src/gl/shaders/basic/default.fragment"
    };

    const char* Material::NoneTexShader_Path[] =
    {
        "src/gl/shaders/basic/none.vertex", "src/gl/shaders/basic/none.fragment"
    };


    Material::Material(Shader* shader, Texture* texture, MaterialAttribs* attribs)
    : m_Shader(shader), m_Texture(texture), m_Attribs(attribs)
    {
        
    }

    Material::Material(const char* scriptPath)
    : m_Shader(nullptr), m_Texture(nullptr), m_Attribs(new MaterialAttribs())
    {
        LoadLuaRes(scriptPath);
    }
    
    void Material::LoadLuaRes(const char *scriptPath)
    {
        LuaScript* script = LuaScript::GetLuaScript(scriptPath, "Mesh");
        if (script == nullptr)
        {
            std::cout<<"[ERROR]: '"<<scriptPath<<"' Lua Script Load Failed. "<<std::endl;
            return;
        }
        
        std::string shaderTableName = "MeshRenderer.Material.Shader";
        std::string vsPath = script->Get<std::string>((shaderTableName + ".vertex_shader_path").c_str());
        std::string fsPath = script->Get<std::string>((shaderTableName + ".fragment_shader_path").c_str());
        m_Shader = new Shader(vsPath, fsPath);
        
        std::string attrTableName = "MeshRenderer.Material.Attributes";
        if (script->Get<std::string>((attrTableName + ".status").c_str()) == "Active")
        {
            ml::Vector3f ambient = script->LuaBridgeGet<ml::Vector3f>((attrTableName + ".ambient").c_str());
            ml::Vector3f diffuse = script->LuaBridgeGet<ml::Vector3f>((attrTableName + ".diffuse").c_str());
            ml::Vector3f specular = script->LuaBridgeGet<ml::Vector3f>((attrTableName + ".specular").c_str());
            float shiness = script->Get<float>((attrTableName + ".shiness").c_str());
            float transparency = script->Get<float>((attrTableName + ".transparency").c_str());
            
            m_Attribs->SetMatAmbient(ambient);
            m_Attribs->SetMatDiffuse(diffuse);
            m_Attribs->SetMatSpecular(specular);
            m_Attribs->SetMatShiness(shiness);
            m_Attribs->SetMatTransparency(transparency);
        }
    }
    
    Material::~Material()
    {
        if (m_Shader!=NULL)
            delete m_Shader;
    }
    
}
