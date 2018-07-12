//
//  MeshRendererPanel.hpp
//  bird
//
//  Created by 汪依尘 on 7/11/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef MeshRendererPanel_hpp
#define MeshRendererPanel_hpp

#include <stdio.h>
#include "GameObjectPanel.hpp"
#include "MeshRenderer.hpp"

namespace gui {
    
    class MeshRendererPanel: public ComponentPanel
    {
    public:
        MeshRendererPanel(MeshRenderer* meshRenderer);
        ~MeshRendererPanel();
    public:
        void OnRender();
        void OnUpdate();
    private:
        void m_OnRender_MaterialEdit();
        void m_OnRender_TextureSelect();
    public:
        inline void BindMeshRenderer(MeshRenderer* meshRenderer) { m_MeshRenderer = meshRenderer; }
        inline void BindComponent(Component* component) { m_MeshRenderer = dynamic_cast<MeshRenderer*>(component);}
    private:
        MeshRenderer* m_MeshRenderer;
        int m_CurrSelectedTexture;
    };
};
#endif /* MeshRendererPanel_hpp */
