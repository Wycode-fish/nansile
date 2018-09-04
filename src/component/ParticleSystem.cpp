//
//  ParticleSystem.cpp
//  bird
//
//  Created by 汪依尘 on 8/24/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ParticleSystem.hpp"
#include "DisplaySys.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "MeshRendererAssimp.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Renderer.hpp"


const char* ParticleObj::Configuration_FilePath = "src/game/basic/script/info/mesh/MeshParticle.lua";


ParticleObj::ParticleObj()
: GameObject("Particle"), m_CurrInstanceCnt(0), m_InstancePositionVBO(0), m_InstanceColorVBO(0), m_Sharpness(0.6f)
{
    MeshRendererBind();
    GLCALL(glGenBuffers(1, &m_InstancePositionVBO));
    GLCALL(glGenBuffers(1, &m_InstanceColorVBO));
}

void ParticleObj::InitParticleObj( std::vector<ParticleProps*>& props )
{
    std::vector<ml::Vector3f> positions;
    std::vector<ml::Vector4f> colors;

    for (auto prop: props)
    {
        positions.push_back(prop->Position);
        colors.push_back(prop->Color);
    }
    m_InstanceVBOInit(positions, colors);
    m_CurrInstanceCnt = static_cast<unsigned>(props.size());
}

void ParticleObj::m_InstanceVBOInit( std::vector<ml::Vector3f>& positions, std::vector<ml::Vector4f>& colors )
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstancePositionVBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(ml::Vector3f) * positions.size(), positions.data(), GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstanceColorVBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(ml::Vector4f) * colors.size(), colors.data(), GL_STATIC_DRAW));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void ParticleObj::MeshRendererBind()
{
    AddComponent<rl::MeshRenderer>(rl::MeshRenderer::BuildFromLuaScript(this, Configuration_FilePath));
}


ParticleObj::~ParticleObj()
{
}

void ParticleObj::OnRender()
{
    rl::MeshRenderer* mr = GetComponent<rl::MeshRenderer>();
    if (mr == NULL)
    {
        std::cout<<"[ERROR]: mesh renderer component hasn't been binded yet."<<std::endl;
        return;
    }
    //        mr->RenderPrepare();
    
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE));
    rl::Shader* shaderPtr = mr->GetMaterial()->GetShader();
    shaderPtr->Use();
    
    shaderPtr->SetUniform1f("u_Sharpness", m_Sharpness);
    shaderPtr->SetUniform1f("u_WinHWRatio", DisplaySys::GetInstance()->GetWinHWRatio());
    shaderPtr->SetUniformVec3f("u_ParticleGeneratorPos", GetTransform()->GetPosition());
    shaderPtr->SetUniformMat4f("u_ProjMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetProjMat());
    shaderPtr->SetUniformMat4f("u_ViewMatrix", DisplaySys::GetInstance()->GetMainCamera()->GetViewMat());
    
    ml::Matrix4f modelMat = ml::Translate(ml::Matrix4f(1.0f), GetTransform()->GetPosition());
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().x, ml::Vector3f(1.0f, 0.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().y, ml::Vector3f(0.0f, 1.0f, 0.0f));
    modelMat = ml::Rotate(modelMat, GetTransform()->GetRotation().z, ml::Vector3f(0.0f, 0.0f, 1.0f));
    modelMat = ml::Scale(modelMat, GetTransform()->GetScale() * 0.5f);
    shaderPtr->SetUniformMat4f("u_ModelMatrix", modelMat);
    
    for (auto mesh: mr->GetModel()->GetMeshes())
    {
        mesh->Use();
    }
    GLCALL(glEnableVertexAttribArray(2));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstancePositionVBO));
    GLCALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glVertexAttribDivisor(2, 1));
    
    GLCALL(glEnableVertexAttribArray(3));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_InstanceColorVBO));
    GLCALL(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glVertexAttribDivisor(3, 1));

    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    mr->DrawInstances(m_CurrInstanceCnt);
}

void ParticleObj::OnRenderOutline()
{
}


/* struct ParticleProps */
ParticleProps::ParticleProps()
: Position( ml::Vector3f(0.0f, 0.0f, 0.0f) ), Velocity( ml::Vector3f(0.0f, 5.0f, 0.0f) ), Color( ml::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) ), LifeTime(0.0f)
{}


/* ParticleSystem */
ParticleSystem::ParticleSystem(GameObject* gameObject, unsigned cnt)
: m_SpawnOnceCnt(2), m_LastUsedIdx(0), m_ParticleCnt(cnt), m_Offset(0.0f), m_AlphaDecayFactor(2.0f), m_FloatingSpeed(0.5f), m_ParticleLifeTime(2.0f), m_SpeedDecayFactor(0.5f), m_ColorPossibility(0.5f), m_Props(m_ParticleCnt, nullptr), m_Timer( Timer::DeltaClock()), m_ParticleObj(new ParticleObj()), Component(gameObject, "Particle System")
{
    InitProps(&m_Props);
}

void ParticleSystem::InitProps(std::vector<ParticleProps*>* props)
{
    unsigned i = 0;
    while ( i < (*props).size())
    {
        (*props)[i++] = new ParticleProps();
    }
}

void ParticleSystem::InitProps(std::vector<ParticleProps*>* props, unsigned cnt)
{
    unsigned i = 0;
    while( i++ < cnt)
    {
        (*props).push_back(new ParticleProps());
    }
}



ParticleSystem::~ParticleSystem()
{
    if (m_ParticleObj != nullptr)
    {
        delete m_ParticleObj;
    }
}

void ParticleSystem::Update()
{
    float dt = m_Timer.GetDelta();
    for (int i=0; i<m_SpawnOnceCnt; i++)
    {
        unsigned nextIdx = m_NextToSpawn();
        m_SpawnParticle(m_Props[nextIdx], GetGameObject()->GetTransform()->GetPosition(), m_Offset);
    }
    
    std::vector<ParticleProps*> renderList;
    
    for (auto prop: m_Props)
    {
        prop->LifeTime -= dt;
        if (prop->LifeTime > 0.0f)
        {
            prop->Position += prop->Velocity * dt;
            prop->Velocity *= 1 - dt * m_SpeedDecayFactor;
            prop->Color.w *= 1 - dt * m_AlphaDecayFactor;
            
            if (prop->Color.w > 0)
                renderList.push_back(prop);
        }
    }
    m_ParticleObj->InitParticleObj(renderList);
    m_ParticleObj->OnRender();
}

void ParticleSystem::m_Draw()
{
    std::vector<ParticleProps*> renderList;
    for (auto prop: m_Props)
    {
        if (prop->LifeTime > 0)
        {
            renderList.push_back(prop);
        }
    }
    m_ParticleObj->InitParticleObj(renderList);
    m_ParticleObj->OnRender();
}

unsigned ParticleSystem::m_NextToSpawn()
{
    for (int i=m_LastUsedIdx; i<m_ParticleCnt; i++)
    {
        if (m_Props[i]->LifeTime <= 0 )
        {
            m_LastUsedIdx = i;
            return i;
        }
    }
    
    for (int i=0; i<m_LastUsedIdx; i++)
    {
        if (m_Props[i]->LifeTime <= 0 )
        {
            m_LastUsedIdx = i;
            return i;
        }
    }
    
    m_LastUsedIdx = 0;
    return 0;
}

void ParticleSystem::m_SpawnParticle(ParticleProps* prop, ml::Vector3f currGameObjectPosition, ml::Vector3f offset)
{
    if (prop == nullptr)
    {
        std::cout<<"[ERROR]: particle prop hasn't been initialized."<<std::endl;
    }
    ml::Vector3f currSpawnScale = m_ParticleObj->GetTransform()->GetScale();
    unsigned xScale = (static_cast<int>(currSpawnScale.x * 10)<1)?1:static_cast<int>(currSpawnScale.x * 10);
    float randPosX = ((rand() % xScale) - xScale / 2.0f) / 10.0f;
    unsigned yScale = (static_cast<int>(currSpawnScale.y * 10)<1)?1:static_cast<int>(currSpawnScale.y * 10);
    float randPosY = ((rand() % yScale) - yScale / 2.0f) / 10.0f;
    unsigned zScale = (static_cast<int>(currSpawnScale.z * 10)<1)?1:static_cast<int>(currSpawnScale.z * 10);
    float randPosZ = ((rand() % zScale) - zScale / 2.0f) / 10.0f;

    float randColorR = 0.5 + ((rand() % static_cast<unsigned>((m_ColorPossibility.x * 100))) / 100.0f);
    float randColorG = 0.5 + ((rand() % static_cast<unsigned>((m_ColorPossibility.y * 100))) / 100.0f);
    float randColorB = 0.5 + ((rand() % static_cast<unsigned>((m_ColorPossibility.z * 100))) / 100.0f);
    
    prop->LifeTime = m_ParticleLifeTime;
    prop->Position = currGameObjectPosition + offset + ml::Vector3f(randPosX, randPosY, randPosZ);
    prop->Color = ml::Vector4f( randColorR, randColorG, randColorB, 1.0f);
    prop->Velocity = ml::Vector3f(0.0f, m_FloatingSpeed, 0.0f);
}

void ParticleSystem::UpdateParticleCnt(unsigned particleCnt)
{
    if (m_Props.size() == particleCnt) return;
    
    for (auto prop: m_Props)
    {
        if (prop!=nullptr) delete prop;
    }
    m_Props.clear();
    
    InitProps(&m_Props, particleCnt);
    m_ParticleCnt = particleCnt;
}

