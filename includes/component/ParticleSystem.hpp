//
//  ParticleSystem.hpp
//  bird
//
//  Created by 汪依尘 on 8/24/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "VertexBuffer.hpp"
#include "Timer.hpp"

struct ParticleProps
{
    ml::Vector3f Position;
    ml::Vector4f Color;
    ml::Vector3f Velocity;
    float LifeTime;
    
    ParticleProps();
};

class ParticleObj: public GameObject
{
public:
    static const char* Configuration_FilePath;
    
public:
    ParticleObj();
    ~ParticleObj();
    void MeshRendererBind() override;
    void OnRender() override;
    void OnRenderOutline() override;
    
public:
    void InitParticleObj( std::vector<ParticleProps*>& props );
    
public:
    inline float& GetSharpness() { return m_Sharpness; }
    
private:
    void m_InstanceVBOInit( std::vector<ml::Vector3f>& positions, std::vector<ml::Vector4f>& colors );
    
private:
    unsigned m_InstancePositionVBO;
    unsigned m_InstanceColorVBO;
    unsigned m_InstanceVBO;
    unsigned m_CurrInstanceCnt;
    float    m_Sharpness;
};


class ParticleSystem : public Component
{
public:
    ParticleSystem(GameObject* gameObject, unsigned cnt = 500);
    ~ParticleSystem();
    
public:
    void Update() override;
    unsigned m_NextToSpawn();
    void m_SpawnParticle(ParticleProps* particle, ml::Vector3f currGameObjectPosition, ml::Vector3f offset);
    void m_Draw();
    
public:
    void UpdateParticleCnt(unsigned particleCnt);
    
public:
    inline int GetParticleCnt() { return m_ParticleCnt; }
    inline ParticleObj* GetParticleObj() { return m_ParticleObj; }
    
    inline float& GetAlphaDecayRef() { return m_AlphaDecayFactor; }
    inline float& GetFloatingSpeedRef() { return m_FloatingSpeed; }
    inline float& GetParticleLifeRef() { return m_ParticleLifeTime; }
    inline float& GetSpeedDecayFactorRef() { return m_SpeedDecayFactor; }
    inline ml::Vector3f& GetColorPossibility() { return m_ColorPossibility; }
    
    inline void SetOffset(const ml::Vector3f& offset) { m_Offset = offset; }
private:
    void InitProps(std::vector<ParticleProps*>* props);
    void InitProps(std::vector<ParticleProps*>* props, unsigned cnt);
    
private:
    unsigned m_LastUsedIdx;
    unsigned m_SpawnOnceCnt;
    Timer    m_Timer;
    int      m_ParticleCnt;
    ml::Vector3f m_Offset;
    
    float    m_AlphaDecayFactor;
    float    m_FloatingSpeed;
    float    m_ParticleLifeTime;
    float    m_SpeedDecayFactor;
    
    ml::Vector3f m_ColorPossibility;
    
    std::vector<ParticleProps*> m_Props;
    ParticleObj* m_ParticleObj;
};

#endif /* ParticleSystem_hpp */
