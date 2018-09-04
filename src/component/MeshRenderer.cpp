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
#include "CubeMap.hpp"

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
        std::vector<std::string> texturePaths = resScript->GetVector<std::string>("Mesh.texture.texture_paths");
        rl::Texture* texture = (texturePaths.size() == 0)? nullptr : (texturePaths.size() > 1)? rl::CubeMap::GetCubeMap(texturePaths) : rl::Texture::GetTexture(texturePaths[0].c_str());

        
        unsigned int vertexCntPerSide = resScript->Get<unsigned int>("Mesh.model.vertex_count_per_surface");
        unsigned int surfaceCnt = resScript->Get<unsigned int>("Mesh.model.surface_count");
        unsigned int attrFloatPerVtx = resScript->Get<unsigned int>("Mesh.model.attr_float_per_vertex");
        unsigned int idxPerSurface = resScript->Get<unsigned int>("Mesh.model.idx_per_surface");
        
        std::vector<unsigned int> floatPerData = resScript->GetVector<unsigned int>("Mesh.model.layout_elements");
        rl::VertexBufferLayout layout;
        for (int i=0; i<floatPerData.size(); i++)
        {
            layout.Add<float>(floatPerData[i], GL_FALSE);
        }
        
        unsigned int vtxPosSize = surfaceCnt * vertexCntPerSide * attrFloatPerVtx * sizeof(float);
        
        unsigned int vtxIdxCnt = surfaceCnt * idxPerSurface;
        std::vector<float> vp = resScript->GetVector<float>("Mesh.model.vertex_position");
        
        float* vposData = new float[vp.size()];
        for (int i=0; i<vp.size(); i++)
        {
            vposData[i] = vp[i];
        }
        std::vector<unsigned> idxs = resScript->GetVector<unsigned int>("Mesh.model.vertex_indicies");
        unsigned* idxData = new unsigned[idxs.size()];
        for (int i=0; i<idxs.size(); i++)
        {
            idxData[i] = idxs[i];
        }
        std::string vsPath = resScript->Get<std::string>("Mesh.shader.vertex_shader_path");
        std::string fsPath = resScript->Get<std::string>("Mesh.shader.fragment_shader_path");
        
        return new MeshRenderer(nullptr,
                                { vposData, vtxPosSize, layout, idxData, vtxIdxCnt },
                                new rl::Material(new rl::Shader( vsPath, fsPath), texture));
    }

    return nullptr;
}

MeshRenderer::MeshRenderer(GameObject* gameObject, rl::MeshElement_Group mElement, rl::Material* material)
: m_Mesh(NULL), m_Material(material), m_Renderer(NULL), m_IsActive(true), Component(gameObject, "Mesh Renderer")
{
    m_Mesh = new rl::Mesh(mElement.m_VboData,
                          mElement.m_VboSize,
                          mElement.m_VboLayout,
                          (const unsigned int*)mElement.m_IboData,
                          mElement.m_IboCnt);
    m_Renderer = new rl::Renderer();
}

MeshRenderer::MeshRenderer(GameObject* gameObject, const std::vector<rl::MeshElement> elements, rl::Material* material)
: m_Mesh(NULL), m_Material(material), m_Renderer(NULL), Component(gameObject, "Mesh Renderer")
{
    MeshInit(elements);
    m_Renderer = new rl::Renderer();
}

void MeshRenderer::MeshInit(const std::vector<rl::MeshElement>& elements)
{
    std::vector<rl::VertexBuffer*> vbos;
    rl::IndexBuffer* ibo = NULL;
    for (int i=0; i<elements.size(); i++)
    {
        rl::MeshElement elem = elements[i];
        if (elem.m_Tag == rl::MeshElement::VBO)
        {
            rl::VertexBuffer* vbo = new rl::VertexBuffer(elem.m_Data, elem.m_Type, elem.m_ElemPerVer, elem.m_VtxCnt, elem.m_Normalized);
            vbos.push_back(vbo);
        }
        else if (elem.m_Tag == rl::MeshElement::IBO)
        {
            ibo = new rl::IndexBuffer((const unsigned int*)elem.m_Data, elem.m_VtxCnt);
        }
    }
    m_Mesh = new rl::Mesh(vbos, ibo);
}

void MeshRenderer::Render()
{
    Draw();
    m_Renderer->Clear();
}

void MeshRenderer::Draw()
{
    m_Mesh->Use();
    if (m_Material->GetTexture()!=NULL && strcmp(m_Material->GetTexture()->GetFilePath(), "")!=0)
    {
        m_Material->GetTexture()->Bind();
    }
    m_Material->GetShader()->Use();
    if (m_IsActive)
        m_Renderer->Draw(*m_Mesh);
    else
        m_Renderer->DrawLines(*m_Mesh);
}

MeshRenderer::~MeshRenderer()
{
    if (m_Mesh!=NULL)
        delete m_Mesh;
    if (m_Renderer!=NULL)
        delete m_Renderer;
}

void MeshRenderer::Reload(rl::MeshElement_Group mElement, rl::Shader* shader, rl::Texture* texture)
{
    m_Material->SetShader(shader);
    m_Material->SetTexture(texture);
    m_Mesh = new    rl::Mesh(mElement.m_VboData,
                             mElement.m_VboSize,
                             mElement.m_VboLayout,
                             (const unsigned int*)mElement.m_IboData,
                             mElement.m_IboCnt);
}

void MeshRenderer::ApplyLight(Light* light)
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
    
    rl::Shader* shaderPtr = m_Material->GetShader();
    shaderPtr->Use();
    if (GetMaterial()->GetTexture()!=NULL)
    {
        shaderPtr->SetUniform1i("u_Texture", 0);
        shaderPtr->SetUniform1i("u_TextureExist", 1);
    }
    rl::MaterialAttribs* attribs = GetMaterial()->GetAttribs();
    ml::Vector3f mat_ambient = attribs->m_Ambient;
    ml::Vector3f mat_diffuse = attribs->m_Diffuse;
    ml::Vector3f mat_specular = attribs->m_Specular;
    float mat_shiness = attribs->m_Shiness;
    float transparency = attribs->m_Transparency;

    shaderPtr->SetUniform3f("u_Material.ambient",  mat_ambient.x, mat_ambient.y, mat_ambient.z);
    shaderPtr->SetUniform3f("u_Material.diffuse",  mat_diffuse.x, mat_diffuse.y, mat_diffuse.z);
    shaderPtr->SetUniform3f("u_Material.specular", mat_specular.x, mat_specular.y, mat_specular.z);
    shaderPtr->SetUniform1f("u_Material.shiness", mat_shiness);
    shaderPtr->SetUniform1f("u_Material.transparency", transparency);

}


