//
//  MeshRenderer.cpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "MeshRenderer.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "LuaScript.hpp"
#include "Cube.hpp"

float DefaultVPos[] =
{
    -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f
};
float DefaultTcs[] =
{
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};
unsigned int DefaultIndexData[] =
{
    0, 1, 2,
    2, 3, 0
};

MeshRenderer* MeshRenderer::BuildFromScript(const char* scriptPath)
{
    LuaScript* resScript = LuaScript::GetLuaScript(scriptPath, "Mesh Resource");
    if (resScript != nullptr)
    {
        unsigned int vertexCntPerSide = resScript->Get<unsigned int>("Mesh.model.vertex_count_per_surface");
        unsigned int surfaceCnt = resScript->Get<unsigned int>("Mesh.model.surface_count");
        unsigned int attrFloatPerVtx = resScript->Get<unsigned int>("Mesh.model.attr_float_per_vertex");
        unsigned int idxPerSurface = resScript->Get<unsigned int>("Mesh.model.idx_per_surface");
        
        std::vector<unsigned int> floatPerData = resScript->GetVector<unsigned int>("Mesh.model.layout_elements");
        VertexBufferLayout layout;
        for (int i=0; i<floatPerData.size(); i++)
        {
            layout.Add<float>(floatPerData[i], GL_FALSE);
        }
        
        unsigned int vtxPosSize = surfaceCnt * vertexCntPerSide * attrFloatPerVtx * sizeof(float);
        
        unsigned int vtxIdxCnt = surfaceCnt * idxPerSurface;
        
        return new MeshRenderer(nullptr, {  resScript->GetVector<float>("Mesh.model.vertex_position").data(),
                                            vtxPosSize,
                                            layout,
                                            resScript->GetVector<unsigned int>("Mesh.model.vertex_indicies").data(), vtxIdxCnt },
                                new Material(new Shader(resScript->Get<std::string>("Mesh.shader.vertex_shader_path"), resScript->Get<std::string>("Mesh.shader.fragment_shader_path"))));
    }

    return nullptr;
}

MeshRenderer::MeshRenderer(GameObject* gameObject, ModelElement_Group mElement, Material* material)
: m_Model(NULL), m_Material(material), m_Renderer(NULL), m_IsActive(true), Component(gameObject, "Mesh Renderer")
{
    m_Model = new Model(mElement.m_VboData,
                        mElement.m_VboSize,
                        mElement.m_VboLayout,
                        new IndexBuffer((const unsigned int*)mElement.m_IboData, mElement.m_IboCnt));
    m_Renderer = new Renderer();
}

MeshRenderer::MeshRenderer(GameObject* gameObject, const std::vector<ModelElement> elements, Material* material)
: m_Model(NULL), m_Material(material), m_Renderer(NULL), Component(gameObject, "Mesh Renderer")
{
    ModelInit(elements);
    m_Renderer = new Renderer();
}

void MeshRenderer::ModelInit(const std::vector<ModelElement>& elements)
{
    std::vector<VertexBuffer*> vbos;
    IndexBuffer* ibo = NULL;
    for (int i=0; i<elements.size(); i++)
    {
        ModelElement elem = elements[i];
        if (elem.m_Tag == ModelElement::VBO)
        {
            VertexBuffer* vbo = new VertexBuffer(elem.m_Data, elem.m_Type, elem.m_ElemPerVer, elem.m_VtxCnt, elem.m_Normalized);
            vbos.push_back(vbo);
        }
        else if (elem.m_Tag == ModelElement::IBO)
        {
            ibo = new IndexBuffer((const unsigned int*)elem.m_Data, elem.m_VtxCnt);
        }
    }
    m_Model = new Model(vbos, ibo);
}

void MeshRenderer::Render()
{
    Draw();
    m_Renderer->Clear();
}

void MeshRenderer::Draw()
{
    m_Model->Use();
    if (m_Material->GetTexture()!=NULL && strcmp(m_Material->GetTexture()->GetFilePath(), "")!=0)
    {
        m_Material->GetTexture()->Bind();
    }
    m_Material->GetShader()->Use();
    if (m_IsActive)
        m_Renderer->Draw(*m_Model);
    else
        m_Renderer->DrawLines(*m_Model);
}

MeshRenderer::~MeshRenderer()
{
    if (m_Model!=NULL)
        delete m_Model;
    if (m_Renderer!=NULL)
        delete m_Renderer;
}

void MeshRenderer::Reload(ModelElement_Group mElement, Shader* shader, Texture* texture)
{
    m_Material->SetShader(shader);
    m_Material->SetTexture(texture);
    m_Model = new Model(mElement.m_VboData,
                        mElement.m_VboSize,
                        mElement.m_VboLayout,
                        new IndexBuffer((const unsigned int*)mElement.m_IboData, mElement.m_IboCnt));
}

void MeshRenderer::ApplyLight(Light* light)
{
    glm::vec3 ambient = light->GetAttribs()->m_Ambient;
    glm::vec3 diffuse = light->GetAttribs()->m_Diffuse;
    glm::vec3 specular = light->GetAttribs()->m_Specular;
    glm::vec3 attenuation = light->GetAttribs()->m_Attenuation;
    glm::vec3 color = light->GetAttribs()->m_Color;
    float intensity = light->GetAttribs()->m_Intensity;
    
    glm::vec3 pos = light->GetTransform()->GetPosition();
    glm::vec3 rot = light->GetTransform()->GetRotation();
    
    Shader* shaderPtr = m_Material->GetShader();
    shaderPtr->Use();
    shaderPtr->SetUniform3f("u_LightPos", pos.x, pos.y, pos.z);
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

void MeshRenderer::RenderPrepare()
{
    for (int i=0; i<Light::ActiveLights.size(); i++)
    {
        ApplyLight(Light::ActiveLights[i]);
    }
    
    Shader* shaderPtr = m_Material->GetShader();
    shaderPtr->Use();
    if (GetMaterial()->GetTexture()!=NULL)
    {
        shaderPtr->SetUniform1i("u_Texture", 0);
        shaderPtr->SetUniform1i("u_TextureExist", 1);
    }
    MaterialAttribs* attribs = GetMaterial()->GetAttribs();
    glm::vec3 mat_ambient = attribs->m_Ambient;
    glm::vec3 mat_diffuse = attribs->m_Diffuse;
    glm::vec3 mat_specular = attribs->m_Specular;
    float mat_shiness = attribs->m_Shiness;
    float transparency = attribs->m_Transparency;

    shaderPtr->SetUniform3f("u_Material.ambient",  mat_ambient.x, mat_ambient.y, mat_ambient.z);
    shaderPtr->SetUniform3f("u_Material.diffuse",  mat_diffuse.x, mat_diffuse.y, mat_diffuse.z);
    shaderPtr->SetUniform3f("u_Material.specular", mat_specular.x, mat_specular.y, mat_specular.z);
    shaderPtr->SetUniform1f("u_Material.shiness", mat_shiness);
    shaderPtr->SetUniform1f("u_Material.transparency", transparency);

}


