//
//  ParticleSystemPanel.hpp
//  bird
//
//  Created by 汪依尘 on 8/30/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ParticleSystemPanel_hpp
#define ParticleSystemPanel_hpp

#include <stdio.h>
#include "GameObjectPanel.hpp"
#include "ParticleSystem.hpp"
#include <vector>

namespace gui {
    class ParticleSystemPanel: public ComponentPanel
    {
    public:
        ParticleSystemPanel(ParticleSystem* ParticleSystem);
        ~ParticleSystemPanel();
    public:
        void OnRender();
        void OnUpdate();
    public:
        inline void BindParticleSystem(ParticleSystem* particleSystem) { m_ParticleSystem = particleSystem; }
        inline void BindComponent(Component* component) { m_ParticleSystem = dynamic_cast<ParticleSystem*>(component);}
    private:
        ParticleSystem*   m_ParticleSystem;
        int               m_CurrParticleCnt;
    };
}



#endif /* ParticleSystemPanel_hpp */
