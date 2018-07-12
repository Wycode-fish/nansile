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

MeshRenderer::MeshRenderer(GameObject* gameObject, ModelElement_Group mElement, const std::shared_ptr<Material> material)
: m_Model(NULL), m_Material(material), m_Renderer(NULL), Component(gameObject, "Mesh Renderer")
{
    m_Model = new Model(mElement.m_VboData,
                        mElement.m_VboSize,
                        mElement.m_VboLayout,
                        new IndexBuffer((const unsigned int*)mElement.m_IboData, mElement.m_IboCnt));
    m_Renderer = new Renderer();
}

MeshRenderer::MeshRenderer(GameObject* gameObject, const std::vector<ModelElement> elements, const std::shared_ptr<Material> material)
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
//        std::cout<<"test "<<m_Material->GetTexture()->GetFilePath()<<std::endl;
    }
    m_Material->GetShader()->Use();
    glDrawElements(GL_TRIANGLES, m_Model->GetCount(), GL_UNSIGNED_INT, nullptr);
}

MeshRenderer::~MeshRenderer()
{
    if (m_Model!=NULL)
        delete m_Model;
    if (m_Renderer!=NULL)
        delete m_Renderer;
}

void MeshRenderer::Reload(ModelElement_Group mElement, const std::shared_ptr<Shader> shader, const std::shared_ptr<Texture> texture)
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
    
    glm::vec3 pos = light->GetTransform()->GetPosition();
    
    std::shared_ptr<Shader> shaderPtr = m_Material->GetShader();
    shaderPtr->Use();
    shaderPtr->SetUniform3f("u_LightPos", pos.x, pos.y, pos.z);
    shaderPtr->SetUniform3f("u_LightColor", color.x, color.y, color.z);
    shaderPtr->SetUniform3f("u_Light.ambient", ambient.x, ambient.y, ambient.z);
    shaderPtr->SetUniform3f("u_Light.diffuse", diffuse.x, diffuse.y, diffuse.z);
    shaderPtr->SetUniform3f("u_Light.specular", specular.x, specular.y, specular.z);
    shaderPtr->SetUniform1f("u_Light.attenuation_Kc", attenuation[ATTENUATION_KC]);
    shaderPtr->SetUniform1f("u_Light.attenuation_Kl", attenuation[ATTENUATION_KL]);
    shaderPtr->SetUniform1f("u_Light.attenuation_Kq", attenuation[ATTENUATION_KQ]);
}

void MeshRenderer::RenderPrepare()
{
    for (int i=0; i<Light::ActiveLights.size(); i++)
    {
        ApplyLight(Light::ActiveLights[i]);
    }
    
    std::shared_ptr<Shader> shaderPtr = m_Material->GetShader();
    shaderPtr->Use();
    if (GetMaterial()->GetTexture().get()!=NULL)
    {
        shaderPtr->SetUniform1i("u_Texture", 0);
        shaderPtr->SetUniform1i("u_TextureExist", 1);
    }
    MaterialAttribs* attribs = GetMaterial()->GetAttribs();
    glm::vec3 mat_ambient = attribs->m_Ambient;
    glm::vec3 mat_diffuse = attribs->m_Diffuse;
    glm::vec3 mat_specular = attribs->m_Specular;
    float mat_shiness = attribs->m_Shiness;

    shaderPtr->SetUniform3f("u_Material.ambient",  mat_ambient.x, mat_ambient.y, mat_ambient.z);
    shaderPtr->SetUniform3f("u_Material.diffuse",  mat_diffuse.x, mat_diffuse.y, mat_diffuse.z);
    shaderPtr->SetUniform3f("u_Material.specular", mat_specular.x, mat_specular.y, mat_specular.z);
    shaderPtr->SetUniform1f("u_Material.shiness", mat_shiness);
}


